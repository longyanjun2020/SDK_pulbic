/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_gui.h"
#include "ahc_isp.h"
#include "ahc_os.h"
#include "ahc_menu_inc.h"
#include "ahc_warningmsg.h"
#include "ahc_parameter.h"
//#include "ahc_general.h"
#include "ahc_display.h"
#include "ahc_media.h"
//#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuSetting.h"
//#include "DrawFileList.h"
#include "DrawStateMenuSetting.h"
#include "drawstatevideofunc.h"
#include "IconDefine.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "dsc_charger.h"
#include "zoomcontrol.h"
#include "mediaplaybackctrl.h"
#include "ui_drawgeneral.h"
#include "OSDStrings.h"
#include "ShowOSDFunc.h"
#if (SUPPORT_GPS)
#include "gps_nmea0183.h"
#include "gps_ctl.h"
#endif
#ifdef _OEM_MENU_
#include "ahc_utility.h"
#include "Oem_Menu.h"
#endif
#include "statetvfunc.h"
#include "statehdmifunc.h"
/*===========================================================================
 * Extern variable
 *===========================================================================*/
extern AHC_BOOL gbAhcDbgBrk;
extern UINT8    m_ubDSCMode;
#ifdef CFG_DRAW_ICON_IN //may be defined in config_xxx.h
extern GUI_CONST_STORAGE GUI_BITMAP  bmIcon_In;
#endif
#if MENU_GENERAL_DRIVER_ID_SETTING_EN
extern char Driverid[10];
#endif
extern AHC_OSD_INSTANCE *m_OSD[];

MMP_BOOL    g_bDrawUnfix    = MMP_FALSE;//Don`t update GPS message if GPS is not location.

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void ________GPS_QuickInfo_Function_________(){ruturn;} //dummy
#endif

void QuickDrawItem_GPSInfo(UINT16 ubID, GUI_COLOR bkColor)
{
#if (SUPPORT_GPS)
    UINT8       i = 0;
    UINT16      uiDegree    = 0, uiMinute = 0;
    double      uiSec       = 0;

    UINT16      offset_x    = 130;
    UINT16      offset_y    = 30;
    UINT16      YSpace      = 20;
    UINT16      GPSSigs_x   = 30;
    UINT16      GPSSigs_y   = 50;

    UINT8*      ubDirChar;
    char        sz[30];
    ST_GPS_INFO *pInfo = (ST_GPS_INFO *) GPS_Information();

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetPenSize(ubID, 3);

    if (AHC_IsTVConnectEx() || AHC_IsHdmiConnect())
    {
    }
    else
    {
        //AHC_OSDDrawBitmap(ubID, &bmIcon_GPSSigs, GPSSigs_x, GPSSigs_y);
        GUI_SelectLayer(ubID);
        GUI_SetRotateDrawMode(m_OSD[ubID]->gui.ulRotateByGUI);
        GUI_SetFlipDrawMode(m_OSD[ubID]->gui.ulFlipByGUI);
    }

    if(!GPSCtrl_GPS_IsValidValue())
    {
        AHC_OSDSetPenSize(ubID, 5);
        AHC_OSDSetColor(ubID, OSD_COLOR_RED);
        AHC_OSDDrawLine(ubID, GPSSigs_x+30, GPSSigs_x+50, GPSSigs_y+20, GPSSigs_y+40);
        AHC_OSDDrawLine(ubID, GPSSigs_x+30, GPSSigs_x+50, GPSSigs_y+40, GPSSigs_y+20);
        AHC_OSDSetPenSize(ubID, 3);
    }

    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(ubID, bkColor);

    AHC_OSDSetFont(ubID, &GUI_Font16B_1);

    if(GPSCtrl_GPS_IsValidValue())
    {
        //Latitude
        offset_y += YSpace;

        GPSCtrl_GPSFormatTrans(pInfo->dwLat, &uiDegree, &uiMinute, &uiSec);

        ubDirChar = (pInfo->dwLat>0)?((UINT8*)"N "):((UINT8*)"S ");

        sprintf(sz, "LAT: %s %2d %2d\'%4d\"", ubDirChar, uiDegree, uiMinute, (UINT16)uiSec);

        AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y, strlen(sz));

        //Longitude
        offset_y += YSpace;

        GPSCtrl_GPSFormatTrans(pInfo->dwLon, &uiDegree, &uiMinute, &uiSec);

        ubDirChar = (pInfo->dwLon>0)?((UINT8*)"E "):((UINT8*)"W ");

        sprintf(sz, "LON: %s %2d %2d\'%4d\"", ubDirChar, uiDegree, uiMinute, (UINT16)uiSec);

        AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y, strlen(sz));

        //Use
        offset_y += YSpace;
        #if(GPS_MODULE == GPS_MODULE_NMEA0183)
        sprintf(sz, "USE: %d", (UINT16)(pInfo->ubTotalSatInUse));
        AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y, strlen(sz));
        #endif
    }
    else
    {
        AHC_OSDDrawText(ubID, (UINT8*)"LAT: UnKnown", offset_x, offset_y+YSpace,   strlen("LAT: UnKnown"));
        AHC_OSDDrawText(ubID, (UINT8*)"LON: UnKnown", offset_x, offset_y+YSpace*2, strlen("LON: UnKnown"));
        #if(GPS_MODULE == GPS_MODULE_NMEA0183)
        sprintf(sz, "USE: %d", (UINT16)(pInfo->ubTotalSatInUse));
        AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+YSpace*3, strlen(sz));
        #endif
    }

    for(i=0;i<12;i++)
    {
        AHC_OSDDrawRect(ubID, 16+i*24, 120, 16+(i+1)*24-4, 200);
    }

    #if (GPS_MODULE == GPS_MODULE_NMEA0183)
    for(i=0;i<12;i++)
    {

        AHC_OSDDrawDec(ubID, pInfo->sSatinfo_GPS.sSat[i].iId, 16+i*24+3, 215, 2);

        if(pInfo->sSatinfo_GPS.sSat[i].iIn_use)
            AHC_OSDSetColor(ubID, OSD_COLOR_GREEN);
        else
            AHC_OSDSetColor(ubID, OSD_COLOR_GRAY);

        AHC_OSDDrawFillRect(ubID, 16+i*24+1, 220-pInfo->sSatinfo_GPS.sSat[i].iSig, 16+(i+1)*24-5, 199);

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);

        #if (DISP_WIDTH == 128)
        if ((i % 2) == 0)
            AHC_OSDDrawDec(ubID, pInfo->sSatinfo_GPS.sSat[i].iSig, RECT_START_X+i*RECT_WIDTH, RECT_START_Y - 18, 2);
        else
            AHC_OSDDrawDec(ubID, pInfo->sSatinfo_GPS.sSat[i].iSig, RECT_START_X+i*RECT_WIDTH, RECT_START_Y - 10, 2);
        #else
        AHC_OSDDrawDec(ubID, pInfo->sSatinfo_GPS.sSat[i].iSig, 16+i*24+3, 170, 2);
        #endif
    }
    #endif  // #if (GPS_MODULE == GPS_MODULE_NMEA0183)

    END_LAYER(ubID);

#endif      // #if (SUPPORT_GPS)
}

void QuickDrawGPSInfoPage(UINT8 ubID, AHC_BOOL bFlag)
{
#if (SUPPORT_GPS)
    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(bFlag == AHC_FALSE)
    {
        BEGIN_LAYER(ubID);

        AHC_OSDSetColor(ubID, OSD_COLOR_BACKGROUND);
        AHC_OSDSetBkColor(ubID, OSD_COLOR_BACKGROUND);

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
        AHC_OSDDrawFillRect(ubID, 0, 30, STRETCH_W(m_OSD[ubID]->width), STRETCH_W(m_OSD[ubID]->height));
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        AHC_OSDDrawFillRect(ubID, 0, 30, STRETCH_W(m_OSD[ubID]->height),STRETCH_H(m_OSD[ubID]->width));
#endif
        AHC_OSDSetColor(ubID, 0xAA000000);

        END_LAYER(ubID);
    }
    else
    {
        QuickDrawItem_GPSInfo(ubID, OSD_COLOR_BACKGROUND);
    }
#endif
}

void OSDDraw_GPSStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (SUPPORT_GPS && OSD_SHOW_GPS_STATUS)

    ST_GPS_INFO     *pInfo;
    UINT16          offset_x        = x;
    UINT16          offset_y        = y;
    UINT16          uiDegree        = 0, uiMinute = 0;
    double          uiSec           = 0;
    UINT8*          ubDirChar;
    UINT16          YSpace          = 20;
    UINT8           PointRad        = 6;
    char            sz[30]          = {0};
    GUI_COLOR       ValidFontClr    = OSD_COLOR_GREEN;
    GUI_COLOR       InvalidFontClr  = OSD_COLOR_RED;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);
    }
#endif

    if( AHC_FALSE == bFlag && (g_bDrawUnfix == MMP_FALSE || GPSCtrl_GPS_IsValidValue()))
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, offset_x, offset_y-5, offset_x+220,  offset_y+150);//TBD
        else {
            AHC_OSDDrawFillRect(ubID, offset_x, offset_y-5, offset_x+140,  offset_y+120);
        }
    }
    else
    {
        if(bLarge==LARGE_SIZE)
        {
            AHC_OSDSetFont(ubID, &GUI_Font32_1);
            YSpace          = 25;
            PointRad        = 8;
            ValidFontClr    = OSD_COLOR_GREEN;
            InvalidFontClr  = 0xEE3030DC;
        }
        else if (bLarge==NORMAL_SIZE)
        {
            AHC_OSDSetFont(ubID, &GUI_Font16B_1);
            YSpace          = 20;
            PointRad        = 6;

            ValidFontClr    = OSD_COLOR_GREEN;
            InvalidFontClr  = OSD_COLOR_RED;
        } else {
            AHC_OSDSetFont(ubID, &GUI_Font8_1);
            YSpace          = 10;
            PointRad        = 3;
            ValidFontClr    = OSD_COLOR_GREEN;
            InvalidFontClr  = OSD_COLOR_RED;
        }

        pInfo = (ST_GPS_INFO *) GPS_Information();

        if(GPSCtrl_GPS_IsValidValue())
        {
            g_bDrawUnfix = MMP_FALSE;

            AHC_OSDSetColor(ubID, ValidFontClr);
            AHC_OSDSetBkColor(ubID, bkColor);

            AHC_OSDDrawText(ubID, (UINT8*)"GPS", offset_x, offset_y, strlen("GPS"));

            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawFillCircle(ubID, offset_x+70 , offset_y+15, PointRad);
            else {
                AHC_OSDDrawFillCircle(ubID, offset_x+40 , offset_y+8, PointRad);
            }

            GPSCtrl_GPSFormatTrans(pInfo->dwLat, &uiDegree, &uiMinute, &uiSec);
            ubDirChar = (pInfo->dwLat>0)?((UINT8*)"N"):((UINT8*)"S");
            sprintf(sz, "LAT: %1s %3d %2d\'%4d\"", ubDirChar, uiDegree, uiMinute, (UINT16)uiSec);
            AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+(YSpace*1), strlen(sz));

            GPSCtrl_GPSFormatTrans(pInfo->dwLon, &uiDegree, &uiMinute, &uiSec);
            ubDirChar = (pInfo->dwLon>0)?((UINT8*)"E"):((UINT8*)"W");
            sprintf(sz, "LON: %1s %3d %2d\'%4d\"", ubDirChar, uiDegree, uiMinute, (UINT16)uiSec);
            AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+(YSpace*2), strlen(sz));

            #if(GPS_MODULE == GPS_MODULE_NMEA0183)
            sprintf(sz, "USE: %02d", (UINT16)(pInfo->ubTotalSatInUse));
            AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+(YSpace*3), strlen(sz));
            #endif
        }
        else if(MMP_FALSE == g_bDrawUnfix)
        {
            g_bDrawUnfix = MMP_TRUE;

            AHC_OSDSetColor(ubID, InvalidFontClr);
            AHC_OSDSetBkColor(ubID, bkColor);

            AHC_OSDDrawText(ubID, (UINT8*)"GPS", offset_x, offset_y, strlen("GPS"));

            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawFillCircle(ubID, offset_x+70 , offset_y+15, PointRad);
            else {
                AHC_OSDDrawFillCircle(ubID, offset_x+40 , offset_y+8, PointRad);
            }
            //TL-> Mantis:1038919
            //Avoid make a incomplete OSD update. There are some residual values when update LAT/LON UnKnown.
            sprintf(sz, "LAT: UnKnown       ");
            AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+(YSpace*1), strlen(sz));

            sprintf(sz, "LON: UnKnown       ");
            AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+(YSpace*2), strlen(sz));

            #if(GPS_MODULE == GPS_MODULE_NMEA0183)
            sprintf(sz, "USE: %02d", (UINT16)(pInfo->ubTotalSatInUse));
            AHC_OSDDrawText(ubID, (UINT8*)sz, offset_x, offset_y+(YSpace*3), strlen(sz));
            #endif
        }
    }

    END_LAYER(ubID);

#endif
}

#if 0
void ________TouchButton_Function_________(){ruturn;} //dummy
#endif

#ifndef _OEM_TOUCH_

void OSDDraw_MainTouchButton(UINT16 ubID, UINT8 uiMode)
{
#if (SUPPORT_TOUCH_PANEL)
    RECT  mRECT  = RECT_SHOW_CTRL_PAGE;
    RECT  RectOK    = RECT_TOUCH_BUTTON_OK;
    RECT  RectMenu  = RECT_TOUCH_BUTTON_MENU;
    RECT  RectMode  = RECT_TOUCH_BUTTON_MODE;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    //BEGIN_LAYER(ubID);
    AHC_OSDSetColor(ubID, 0xAA000000);

    // AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Zoom_In, mRECT.uiLeft, mRECT.uiTop);
    AHC_OSDDrawBitmap(ubID, &bmIcon_OK,                         RectOK.uiLeft,   RectOK.uiTop);
    AHC_OSDDrawBitmap(ubID, &bmIcon_Menu,                       RectMenu.uiLeft, RectMenu.uiTop);
    OSD_ShowStringPool3(ubID, IDS_DS_MENU, RectMenu, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
    AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Movie_Playback,      RectMode.uiLeft, RectMode.uiTop);
    //END_LAYER(ubID);
#endif
}
#endif

void OSDDraw_CtrlTouchButton(UINT16 ubID, UINT8 uiMode)
{
#if (SUPPORT_TOUCH_PANEL)
    RECT  mRECT     = RECT_SHOW_CTRL_PAGE;
    RECT  RectUp    = RECT_TOUCH_BUTTON_UP;
    RECT  RectDn    = RECT_TOUCH_BUTTON_DOWN;
    RECT  RectOK    = RECT_TOUCH_BUTTON_OK;
    RECT  RectMenu  = RECT_TOUCH_BUTTON_MENU;
    RECT  RectMode  = RECT_TOUCH_BUTTON_MODE;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    //BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, 0xAA000000);

    switch(uiMode)
    {
        case UI_VIDEO_STATE:
            AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Zoom_In,             mRECT.uiLeft,    mRECT.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_D_Up,                       RectUp.uiLeft,   RectUp.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_D_Down,                     RectDn.uiLeft,   RectDn.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_OK,                         RectOK.uiLeft,   RectOK.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_Menu,                       RectMenu.uiLeft, RectMenu.uiTop);
            OSD_ShowStringPool3(ubID, IDS_DS_MENU, RectMenu, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
            AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Movie_Playback,      RectMode.uiLeft, RectMode.uiTop);
        break;

        case UI_CAMERA_STATE:
            AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Zoom_In,             mRECT.uiLeft,    mRECT.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_D_Up,                       RectUp.uiLeft,   RectUp.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_D_Down,                     RectDn.uiLeft,   RectDn.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_OK,                         RectOK.uiLeft,   RectOK.uiTop);
            AHC_OSDDrawBitmap(ubID, &bmIcon_Menu,                       RectMenu.uiLeft, RectMenu.uiTop);
            OSD_ShowStringPool3(ubID, IDS_DS_MENU, RectMenu, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
            AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Movie_Playback,      RectMode.uiLeft, RectMode.uiTop);
        break;

        case UI_BROWSER_STATE:

        break;

        case UI_PLAYBACK_STATE:
            if( JPGPB_MODE == GetCurrentOpMode())
            {
            #ifdef CFG_DRAW_ICON_IN //may be defined in config_xxx.h
                AHC_OSDDrawBitmap(ubID, &bmIcon_In,         mRECT.uiLeft,    mRECT.uiTop);
            #else
                AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Zoom_In,         mRECT.uiLeft,    mRECT.uiTop);
            #endif
                AHC_OSDDrawBitmap(ubID, &bmIcon_Previous,               RectUp.uiLeft+2, RectUp.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Next,                   RectDn.uiLeft+2, RectDn.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Play_Play,              RectOK.uiLeft-2, RectOK.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Menu,                   RectMenu.uiLeft, RectMenu.uiTop);
                OSD_ShowStringPool3(ubID, IDS_DS_MENU, RectMenu, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Return,                 RectMode.uiLeft, RectMode.uiTop);
            }
            else if( MOVPB_MODE == GetCurrentOpMode() )
            {
                #ifdef CFG_DRAW_ICON_IN //may be defined in config_xxx.h
                AHC_OSDDrawBitmap(ubID, &bmIcon_In,         mRECT.uiLeft,    mRECT.uiTop);
                #else
                AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Zoom_In,         mRECT.uiLeft,    mRECT.uiTop);
                #endif
                AHC_OSDDrawBitmap(ubID, &bmIcon_Movie_Fast_Reverse,     RectUp.uiLeft,   RectUp.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Movie_Fast_Forward,     RectDn.uiLeft,   RectDn.uiTop);

                if(MOV_STATE_PAUSE == GetMovConfig()->iState)
                    AHC_OSDDrawBitmap(ubID, &bmIcon_Play_Play,          RectOK.uiLeft,   RectOK.uiTop+2);
                else
                    AHC_OSDDrawBitmap(ubID, &bmIcon_Play_Pause,         RectOK.uiLeft-2, RectOK.uiTop-10);

                AHC_OSDDrawBitmap(ubID, &bmIcon_Menu,                   RectMenu.uiLeft, RectMenu.uiTop);
                OSD_ShowStringPool3(ubID, IDS_DS_MENU, RectMenu, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Return,                 RectMode.uiLeft, RectMode.uiTop);
            }
            else if( JPGPB_MOVPB_MODE == GetCurrentOpMode())
            {
            #ifdef CFG_DRAW_ICON_IN //may be defined in config_xxx.h
                AHC_OSDDrawBitmap(ubID, &bmIcon_In,         mRECT.uiLeft,    mRECT.uiTop);
            #else
                AHC_OSDDrawBitmap(ubID, &bmIcon_Button_Zoom_In,         mRECT.uiLeft,    mRECT.uiTop);
            #endif
                AHC_OSDDrawBitmap(ubID, &bmIcon_Previous,               RectUp.uiLeft+2, RectUp.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Next,                   RectDn.uiLeft+2, RectDn.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Play_Play,              RectOK.uiLeft-2, RectOK.uiTop);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Menu,                   RectMenu.uiLeft, RectMenu.uiTop);
                OSD_ShowStringPool3(ubID, IDS_DS_MENU, RectMenu, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
                AHC_OSDDrawBitmap(ubID, &bmIcon_Return,                 RectMode.uiLeft, RectMode.uiTop);
            }
        break;

        default:
        break;
    }
    //END_LAYER(ubID);
#endif
}

#if 0
void ________MenuSetting_Function_________(){ruturn;} //dummy
#endif

void OSDDraw_DateTime(UINT8 ubID, int x, int y, int WordWidth, void* vptime)
{
    UINT16  leftpos = x;
    AHC_RTC_TIME* ptime = (AHC_RTC_TIME*)vptime;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    //BEGIN_LAYER(ubID);
    switch(MenuSettingConfig()->uiDateTimeFormat)
    {
        case DATETIME_SETUP_YMD:
            AHC_OSDDrawDec(ubID, ptime->uwYear, leftpos, y, 4);
            leftpos += 4*WordWidth;

            AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
            leftpos += WordWidth;

            AHC_OSDDrawDec(ubID, ptime->uwMonth, leftpos, y, 2);
            leftpos += 2*WordWidth;

            AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
            leftpos += WordWidth;

            AHC_OSDDrawDec(ubID, ptime->uwDay, leftpos, y, 2);
            leftpos += 2*WordWidth;
        break;

        case DATETIME_SETUP_MDY:

            AHC_OSDDrawDec(ubID, ptime->uwMonth, leftpos, y, 2);
            leftpos += 2*WordWidth;

            AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
            leftpos += WordWidth;

            AHC_OSDDrawDec(ubID, ptime->uwDay, leftpos, y, 2);
            leftpos += 2*WordWidth;

            AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
            leftpos += WordWidth;

            AHC_OSDDrawDec(ubID, ptime->uwYear, leftpos, y, 4);
            leftpos += 4*WordWidth;
        break;

        case DATETIME_SETUP_DMY:

            AHC_OSDDrawDec(ubID, ptime->uwDay, leftpos, y, 2);
            leftpos += 2*WordWidth;

            AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
            leftpos += WordWidth;

            AHC_OSDDrawDec(ubID, ptime->uwMonth, leftpos, y, 2);
            leftpos += 2*WordWidth;

            AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
            leftpos += WordWidth;

            AHC_OSDDrawDec(ubID, ptime->uwYear, leftpos, y, 4);
            leftpos += 4*WordWidth;
        break;
    }

    //Draw hour/min/sec
    leftpos += 5;

    AHC_OSDDrawDec(ubID, ptime->uwHour, leftpos, y, 2);
    leftpos += 2*WordWidth;

    AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
    leftpos += WordWidth;

    AHC_OSDDrawDec(ubID, ptime->uwMinute, leftpos, y, 2);
    leftpos += 2*WordWidth;

    AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
    leftpos += WordWidth;

    AHC_OSDDrawDec( ubID, ptime->uwSecond, leftpos, y, 2);
    //END_LAYER(ubID);
}

void OSDDraw_CurrentRTCTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_RTC_TIME)

    UINT16          WordWidth;
    UINT32          ulSysStatus;
    AHC_RTC_TIME    CurRtctime;

    if(MenuSettingConfig()->uiDateTimeFormat==DATETIME_SETUP_NONE)
        return;

    AHC_GetSystemStatus(&ulSysStatus);
    ulSysStatus >>= 16;

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
    }
#endif

    if((ulSysStatus == AHC_MODE_VIDEO_RECORD        ||
        ulSysStatus == AHC_MODE_RECORD_PRERECD  ||
        ulSysStatus == AHC_MODE_RECORD_PREVIEW  ||
        ulSysStatus == AHC_MODE_CAPTURE_PREVIEW     ||
        ulSysStatus == AHC_MODE_RAW_PREVIEW )       &&
        (bFlag == AHC_TRUE ) )
    {
        AHC_RTC_GetTime(&CurRtctime);

        AHC_OSDSetColor(ubID, OSD_COLOR_YELLOW);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
        {
            WordWidth = 15;
            AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
        }
        else
        {
            WordWidth = 10;
            AHC_OSDSetFont(ubID, &GUI_Font20B_1);
        }

        OSDDraw_DateTime(ubID, x, y, WordWidth, (void*)&CurRtctime);
    }
    else
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID,  x, y, 200, 240);//TBD
        AHC_OSDSetColor(ubID, 0xAA000000);
    }

    END_LAYER(ubID);
#endif
}

void OSDDraw_DigitZoomBar(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1, UINT8 ubMode)
{
    static UINT16 uwDigZoomIdx  = 0;

    UINT16      MaxBarLine      = 90;
    UINT16      BarPos          = 0;
    UINT16      BarStartX       = x;
    UINT16      BarStartY       = y;
    UINT32      uwDigZoomRatio  = 1;
    UINT32      uwDigZoomRatioMax;
    UINT16      uwDigZoomIdxTemp;
    UINT16      uwDigZoomIdxMax;
    UINT16      Pensize1, Pensize2;
    const GUI_FONT* pFont1;
    const GUI_FONT* pFont2;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(ubMode==UI_CAMERA_STATE)
    {
        uwDigZoomIdxTemp  = ZoomCtrl_GetStillDigitalZoomLevel();
        uwDigZoomIdxMax   = ZoomCtrl_GetStillDigitalZoomMax();
        uwDigZoomRatioMax = DSC_DIGIT_ZOOM_RATIO_MAX;
    }
    else if(ubMode==UI_VIDEO_STATE)
    {
        uwDigZoomIdxTemp  = ZoomCtrl_GetVideoDigitalZoomLevel();
        uwDigZoomIdxMax   = ZoomCtrl_GetVideoDigitalZoomMax();
        uwDigZoomRatioMax = VIDEO_DIGIT_ZOOM_RATIO_MAX;
    }

    if(bLarge==LARGE_SIZE)
    {
        if(ubMag==MAG_3X)
        {
            MaxBarLine = 350;
            Pensize1   = 9;
            Pensize2   = 3;
            pFont1     = &GUI_Font20B_1;
            pFont2     = &GUI_Font24B_1;
        }
        else if(ubMag==MAG_2X)
        {
            MaxBarLine = 200;
            Pensize1   = 9;
            Pensize2   = 3;
            pFont1     = &GUI_Font20B_1;
            pFont2     = &GUI_Font24B_1;
        }
    }
    else
    {
#ifdef CFG_DRAW_SCREEN_128 //may be defined in config_xxx.h, while using tiny screen width for 128 px
        MaxBarLine = 40;
        Pensize1   = 3;
        Pensize2   = 1;
        pFont1     = &GUI_Font8_1;
        pFont2     = &GUI_Font8_1;
#else
        MaxBarLine = 90;
        Pensize1   = 3;
        Pensize2   = 1;
        pFont1     = &GUI_Font16B_1;
        pFont2     = &GUI_Font20B_1;
#endif
    }

    if(uwDigZoomIdx == uwDigZoomIdxTemp && !Para1)
        return;

    BEGIN_LAYER(ubID);

    uwDigZoomIdx = uwDigZoomIdxTemp;

    //printc("uwDigZoomIdx=%d\r\n",uwDigZoomIdx);

    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(ubID, bkColor);
    AHC_OSDSetFont(ubID, pFont1);

    //Draw text 'W' and 'T'
    if(uwDigZoomIdx == 0)
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_YELLOW);
    }
    else
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    }

    AHC_OSDDrawText(ubID, (UINT8*)"W", BarStartX-4, BarStartY+MaxBarLine+10, 1);

    if(uwDigZoomIdx == uwDigZoomIdxMax) {
        AHC_OSDSetColor(ubID, OSD_COLOR_RED);
    }
    else
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    }

#ifdef CFG_DRAW_SCREEN_128 //may be defined in config_xxx.h, while using tiny screen width for 128 px
    AHC_OSDDrawText(ubID, (UINT8*)"T", BarStartX-2, BarStartY-18, 1);
#else
    AHC_OSDDrawText(ubID, (UINT8*)"T", BarStartX-2, BarStartY-23, 1);
#endif

    //Draw Zoom Ratio
    AHC_OSDSetFont(ubID, pFont2);
    ZoomCtrl_GetDigitalZoomRatio(&uwDigZoomRatio);

#ifdef CFG_DRAW_ZOOM_BAR_WHEN_ZOOMED //may be defined in config_xxx.h
        if(uwDigZoomRatio!=1)
#endif
        {
            char cRatioText[8];

            AHC_OSDSetColor(ubID, OSD_COLOR_GREEN);

            MEMSET(cRatioText, 0, sizeof(cRatioText));
            sprintf(cRatioText, "%d.%1dx ", (uwDigZoomRatio / 100), (uwDigZoomRatio / 10) % 10);
            AHC_OSDDrawText(ubID, (UINT8*) cRatioText,   BarStartX-5, BarStartY+MaxBarLine+28, strlen(cRatioText));
        }
    #ifdef CFG_DRAW_ZOOM_BAR_WHEN_ZOOMED //may be defined in config_xxx.h
    else
        {
            AHC_OSDSetColor(ubID, bkColor);
            AHC_OSDDrawFillRect(ubID, BarStartX-5, BarStartY+MaxBarLine+28, BarStartX+20, BarStartY+MaxBarLine+48);
            AHC_OSDDrawText(ubID, (UINT8*)"    ", BarStartX-5, BarStartY+MaxBarLine+28, 4);
        }
    #endif

    //Draw Fill Zoom Bar
    AHC_OSDSetPenSize(ubID, Pensize1);
    AHC_OSDSetColor(ubID, OSD_COLOR_RED);
    BarPos = (MaxBarLine * uwDigZoomIdx) / uwDigZoomIdxMax;
    AHC_OSDDrawLine(ubID, BarStartX+1, BarStartX+1, BarStartY+(MaxBarLine-BarPos), BarStartY+MaxBarLine-1);

    AHC_OSDSetColor(ubID, bkColor);
    AHC_OSDDrawLine(ubID, BarStartX+1, BarStartX+1, BarStartY, BarStartY+(MaxBarLine-BarPos));

    //Draw Zoom Bar Rectangle
    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetPenSize(ubID, Pensize2);
    AHC_OSDDrawLine(ubID, BarStartX-Pensize2, BarStartX+Pensize1,   BarStartY-Pensize2,     BarStartY-Pensize2);
    AHC_OSDDrawLine(ubID, BarStartX-Pensize2, BarStartX+Pensize1,   BarStartY+MaxBarLine+1, BarStartY+MaxBarLine+1);
    AHC_OSDDrawLine(ubID, BarStartX-Pensize2, BarStartX-Pensize2,   BarStartY-1,            BarStartY+MaxBarLine+1);
    AHC_OSDDrawLine(ubID, BarStartX+Pensize1, BarStartX+Pensize1,   BarStartY-1,            BarStartY+MaxBarLine+1);

    END_LAYER(ubID);
}

void OSDDrawSetting_EV(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if(MENU_MANUAL_EV_EN != 0)
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+110, y+30);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+60,  y+18);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_GREEN);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
        {
            if(ubMag==MAG_3X)
                AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
            else if(ubMag==MAG_2X)
                AHC_OSDSetFont(ubID, &GUI_Font24_1);
        }
        else {
            AHC_OSDSetFont(ubID, &GUI_Font16B_1);
        }

        switch(Menu_EV_To_AE_EV_BIAS(MenuSettingConfig()->uiEV))
        {
            case AHC_AE_EV_BIAS_M200:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: -2.00", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_M166:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: -1.66", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_M133:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: -1.33", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_M100:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: -1.00", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_M066:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: -0.66", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_M033:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: -0.33", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_0000:
                AHC_OSDDrawText(ubID, (UINT8*)"EV:  0.00", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_P033:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: +0.33", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_P066:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: +0.66", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_P100:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: +1.00", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_P133:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: +1.33", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_P166:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: +1.66", x, y, 10);
            break;
            case AHC_AE_EV_BIAS_P200:
                AHC_OSDDrawText(ubID, (UINT8*)"EV: +2.00", x, y, 10);
            break;
        }
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_WB_Mode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_WB_MODE)

    GUI_BITMAP  IconID  = BMICON_UI_WB_DAYLIGHT;
    GUI_COLOR   IconColor = 0xAA000000;

    return;     // TY Miao - TBD

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect( ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);
        else {
            AHC_OSDDrawFillRect( ubID, x,   y,   x+IconID.XSize+15, y+IconID.YSize);
        }

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiWB )
        {
        #if (MENU_MANUAL_WB_AUTO_EN)
            case WB_AUTO:
                 //IconID = bmIcon_WB_Daylight;//TBD
            break;
        #endif
        #if (MENU_MANUAL_WB_FLUORESCENT1_EN)
            case WB_FLUORESCENT1:
                 IconID = BMICON_UI_WB_FLUO1;
            break;
        #endif
        #if (MENU_MANUAL_WB_DAYLIGHT_EN)
            case WB_DAYLIGHT:
                 IconID = BMICON_UI_WB_DAYLIGHT;
            break;
        #endif
        #if (MENU_MANUAL_WB_FLUORESCENT2_EN)
            case WB_FLUORESCENT2:
                 IconID = BMICON_UI_WB_FLUO2;
            break;
        #endif
        #if (MENU_MANUAL_WB_CLOUDY_EN)
            case WB_CLOUDY:
                 IconID = BMICON_UI_WB_CLOUDY;
            break;
        #endif
        #if (MENU_MANUAL_WB_FLUORESCENT3_EN)
            case WB_FLUORESCENT3:
                 IconID = BMICON_UI_WB_FLUO3;
            break;
        #endif
        #if (MENU_MANUAL_WB_INCANDESCENT_EN)
            case WB_INCANDESCENT:
                 IconID = BMICON_UI_WB_INCANDESCENT;
            break;
        #endif
            default:
                 IconID = BMICON_UI_WB_DAYLIGHT;
            break;
        }

        if(MenuSettingConfig()->uiWB!=WB_AUTO)
        {
            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
            else
                AHC_OSDDrawBitmap(ubID, &IconID, x, y);
        }
        else
        {
            AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
            AHC_OSDSetBkColor(ubID, bkColor);

            if(bLarge==LARGE_SIZE)
            {
                AHC_OSDSetFont(ubID, &GUI_Font32B_1);
                AHC_OSDDrawText(ubID,(UINT8*)"AWB", x ,y+13, strlen("AWB"));
            }
            else
            {
                AHC_OSDSetFont(ubID, &GUI_Font20B_1);
                AHC_OSDDrawText(ubID,(UINT8*)"AWB", x ,y+7, strlen("AWB"));
            }
        }
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_UIMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_UI_MODE)

    GUI_BITMAP  IconID = bmIcon_Movie;
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);

        #ifndef CFG_DRAW_ERASE_SMALL_ICON //may be defined in config_xxx.h
        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);
        else
        #endif
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch( GetCurrentOpMode() )
        {
            case VIDEOREC_MODE:
                 IconID = bmIcon_Movie;
            break;
            case CAPTURE_MODE:

            #if 0//(DSC_MULTI_MODE==DSC_MODE_ALL)
                switch(m_ubDSCMode)
                {
                    case DSC_ONE_SHOT:
                        IconID = bmIcon_Still;
                    break;
                    case DSC_BURST_SHOT:
                        IconID = bmTV_BurstB;
                    break;
                    case DSC_TIME_LAPSE:
                        IconID = bmTV_TimeLapseB;
                    break;
                }
            #else
                 IconID = bmIcon_Still;
            #endif
            break;

            case JPGPB_MODE:
            #ifdef CFG_DRAW_CUS_ICON_JPGPB //may be defined in config_xxx.h, e.g. bmIcon_Still
                 IconID = CFG_DRAW_CUS_ICON_JPGPB;
            #else
                 IconID = bmIcon_Still_Playback;
            #endif
            break;

            case MOVPB_MODE:
            #ifdef CFG_DRAW_CUS_ICON_MOVPB //may be defined in config_xxx.h, e.g. bmIcon_Movie
                 IconID = CFG_DRAW_CUS_ICON_MOVPB;
            #else
                 IconID = bmIcon_Movie_Playback;
            #endif
            break;

            case JPGPB_MOVPB_MODE:
            #ifdef CFG_DRAW_CUS_ICON_MOVPB //may be defined in config_xxx.h, e.g. bmIcon_Movie
                 IconID = CFG_DRAW_CUS_ICON_MOVPB;
            #else
                 IconID = bmIcon_Movie_Playback;
            #endif
            break;

            default:
                 IconID = bmIcon_Movie;
            break;
        }

        if(bLarge==LARGE_SIZE)
        {
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        }
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_ImageSize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_IMAGE_SIZE)
#ifdef  _2MSNR_
    GUI_BITMAP  IconID = BMICON_IMAGESIZE_2M;
#else
#if (MENU_STILL_SIZE_14M_EN)    //Andy Liu TBD
    GUI_BITMAP  IconID  = BMICON_IMAGESIZE_14M;
#else
    GUI_BITMAP  IconID  = BMICON_IMAGESIZE_2M;
#endif
#endif

    UINT8       OffsetX = 7;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-OffsetX-5, y-5, x+IconID.XSize+20,      y+IconID.YSize+20);
        else
            AHC_OSDDrawFillRect(ubID, x-OffsetX,   y,   x-OffsetX+IconID.XSize, y+IconID.YSize);
        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, 0xAA000000);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiIMGSize )
        {
        #if (MENU_STILL_SIZE_30M_EN)
            case IMAGE_SIZE_30M:
                 IconID = BMICON_IMAGESIZE_30M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_14M_EN)
            case IMAGE_SIZE_14M:
                 IconID = BMICON_IMAGESIZE_14M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_12M_EN)
            case IMAGE_SIZE_12M:
                 IconID = BMICON_IMAGESIZE_12M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_8M_EN)
            case IMAGE_SIZE_8M:
                 IconID = BMICON_IMAGESIZE_8M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_5M_EN)
            case IMAGE_SIZE_5M:
                 IconID = BMICON_IMAGESIZE_5M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_3M_EN)
            case IMAGE_SIZE_3M:
                 IconID = BMICON_IMAGESIZE_3M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_2M_WIDE_EN)
            case IMAGE_SIZE_2M:
                 IconID = BMICON_IMAGESIZE_2M;
                 OffsetX = 0;
            break;
        #endif
        #if (MENU_STILL_SIZE_1d2M_EN)
            case IMAGE_SIZE_1_2M:
                 IconID = BMICON_IMAGESIZE_1_2M;
                 OffsetX = 7;
            break;
        #endif
        #if (MENU_STILL_SIZE_VGA_EN)
            case IMAGE_SIZE_VGA:
                 IconID = BMICON_IMAGESIZE_VGA;
                 OffsetX = 7;
            break;
        #endif
            default:
                 #ifdef _2MSNR_
                 IconID = BMICON_IMAGESIZE_2M;
                 #else
#if (MENU_STILL_SIZE_14M_EN)  //Andy Liu TBD
                IconID  = BMICON_IMAGESIZE_14M;
#else
                IconID = BMICON_IMAGESIZE_2M;
#endif
                #endif
                OffsetX = 0;
            break;
        }

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x-OffsetX, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x-OffsetX, y);
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_FlashMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_FLASH_STATUS)

    GUI_BITMAP  IconID = bmIcon_Flash_OFF;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5,  y-5, x+IconID.XSize+20, y+IconID.YSize+30);
        else
            AHC_OSDDrawFillRect(ubID, x,    y,   x+IconID.XSize,    y+IconID.YSize);
    }
    else
    {
#if (LED_FLASH_CTRL==LED_BY_MENU                || \
     LED_FLASH_CTRL==LED_BY_MENU_AND_KEY_LINK   || \
     LED_FLASH_CTRL==LED_BY_MENU_AND_KEY_NOT_LINK)

        switch ( AHC_GetMenuFlashLEDStatus() )
        {
            case LED_FALSH_ON:
                 IconID = bmIcon_Flash_ON;
            break;
            case LED_FALSH_OFF:
                 IconID = bmIcon_Flash_OFF;
            break;
            default:
                 IconID = bmIcon_Flash_ON;
            break;
        }

#elif ( LED_FLASH_CTRL==LED_BY_KEY || \
        LED_FLASH_CTRL==LED_BY_KEY_WITH_MENU_CONFIRMED)

        switch ( MenuSettingConfig()->uiFlashMode )
        {
        #if (MENU_STILL_FLASH_AUTO_EN)
            case FLASH_AUTO:
                 IconID = bmIcon_Flash_Auto;
            break;
        #endif
        #if (MENU_STILL_FLASH_SLOW_SYNC_EN)
            case FLASH_SLOW_SYNC:
                 IconID = bmIcon_Flash_Slow_Sync;
            break;
        #endif
        #if (MENU_STILL_FLASH_ON_EN)
            case FLASH_ON:
                 IconID = bmIcon_Flash_ON;
            break;
        #endif
        #if (MENU_STILL_FLASH_OFF_EN)
            case FLASH_OFF:
                 IconID = bmIcon_Flash_OFF;
            break;
        #endif
            default:
                 IconID = bmIcon_Flash_Auto;
            break;
        }
#endif

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_SelfTimer(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (MENU_STILL_SELF_TIMER_EN && OSD_SHOW_SELF_TIMER)

    GUI_BITMAP  IconID = bmIcon_Selftimer_2S;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if( AHC_FALSE == bFlag || SELF_TIMER_OFF == MenuSettingConfig()->uiSelfTimer )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, 0xAA000000);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiSelfTimer )
        {
        #if (MENU_STILL_SELF_TIMER_2S_EN)
            case SELF_TIMER_2S:
                IconID = BMICON_SELFTIMER_2S;
            break;
        #endif
        #if (MENU_STILL_SELF_TIMER_10S_EN)
            case SELF_TIMER_10S:
                IconID = BMICON_SELFTIMER_10S;
            break;
        #endif
            default:
                IconID = BMICON_SELFTIMER_2S;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);

#endif
}

void OSDDrawSetting_BurstShot(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (MENU_STILL_BURST_SHOT_EN && OSD_SHOW_BURST_SHOT)

    GUI_BITMAP  IconID = bmIcon_Burst_Low;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if( AHC_FALSE == bFlag || BURST_SHOT_OFF == MenuSettingConfig()->uiBurstShot )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, 0xAA000000);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiBurstShot )
        {
        #if (MENU_STILL_BURST_SHOT_LO_EN)
            case BURST_SHOT_LO:
                 IconID = bmIcon_Burst_Low;
            break;
        #endif
        #if (MENU_STILL_BURST_SHOT_MID_EN)
            case BURST_SHOT_MID:
                 IconID = bmIcon_Burst_Middle;
            break;
        #endif
        #if (MENU_STILL_BURST_SHOT_HI_EN)
            case BURST_SHOT_HI:
                 IconID = bmIcon_Burst_High;
            break;
        #endif
            default:
                return;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);

#endif
}

void OSDDrawSetting_MovieSize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_MOVIE_SIZE)

    GUI_BITMAP  IconID = BMICON_MOVIESIZE_720P;
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiMOVSize )
        {
        #if(MENU_MOVIE_SIZE_1440_30P_EN)
        case MOVIE_SIZE_1440_30P:
            IconID = BMICON_MOVIESIZE_1296P;
            break;
        #endif

        #if(MENU_MOVIE_SIZE_SHD_30P_EN)
        case MOVIE_SIZE_SHD_30P:
            IconID = BMICON_MOVIESIZE_1296P;
            break;
        #endif
        #if(MENU_MOVIE_SIZE_SHD_25P_EN)
        case MOVIE_SIZE_SHD_25P:
            IconID = BMICON_MOVIESIZE_1296_25P;
            break;
        #endif
        #if(MENU_MOVIE_SIZE_SHD_24P_EN)
        case MOVIE_SIZE_SHD_24P:
            IconID = BMICON_MOVIESIZE_1296_24P;
            break;
        #endif

        #if(MENU_MOVIE_SIZE_1080_60P_EN)
        case MOVIE_SIZE_1080_60P:
            IconID = BMICON_MOVIESIZE_1080_60P;
            break;
        #endif
        /*
        #if (MENU_MOVIE_SIZE_1080P_30_HDR_EN) || (MENU_MOVIE_SIZE_1080P_30_COMBINED_HDR_EN)
            case MOVIE_SIZE_1080_30P_HDR:
                IconID = BMICON_MOVIESIZE_1080P_HDR;
            break;
        #endif
        */
        #if (MENU_MOVIE_SIZE_1080P_EN)
            case MOVIE_SIZE_1080P:
                IconID = BMICON_MOVIESIZE_1080P;
            break;
        #endif
        #if (MENU_MOVIE_SIZE_1080_24P_EN)
            case MOVIE_SIZE_1080_24P:
                 IconID = BMICON_MOVIESIZE_1080_24P;
            break;
        #endif
        #if (MENU_MOVIE_SIZE_720P_EN)
            case MOVIE_SIZE_720P:
                 IconID = BMICON_MOVIESIZE_720P;
            break;
        #endif
        #if (MENU_MOVIE_SIZE_720_60P_EN)
            case MOVIE_SIZE_720_60P:
                 IconID = BMICON_MOVIESIZE_720_60P;
            break;
        #endif
        #if (MENU_MOVIE_SIZE_720_24P_EN)
            case MOVIE_SIZE_720_24P:
                 IconID = BMICON_MOVIESIZE_720_24P;
            break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA30P_EN)
            case MOVIE_SIZE_VGA_30P:
                 IconID = BMICON_MOVIESIZE_VGA_30P;
            break;
        #endif
        #if (MENU_MOVIE_SIZE_VGA120P_EN)
            case MOVIE_SIZE_VGA_120P:
                 IconID = BMICON_MOVIESIZE_VGA_120P;
            break;
        #endif
            default:
                 IconID = BMICON_MOVIESIZE_720P;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_MediaType(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_MEDIA_TYPE)

    GUI_BITMAP  IconID = BMICON_MEDIA_SD;
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
        AHC_OSDSetBkColor(ubID, bkColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+30, y+IconID.YSize+20);
        else
            AHC_OSDDrawFillRect(ubID, x-2, y,   x+IconID.XSize+2,  y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiMediaSelect )
        {
            case MEDIA_SETTING_SD_CARD:
                if(AHC_SDMMC_GetClass(AHC_SD_0) < SLOW_MEDIA_CLASS)
                    IconID = BMICON_MEDIA_SD_SLOW;
                else
                    IconID = BMICON_MEDIA_SD;
            break;
            case MEDIA_SETTING_SD_CARD_ERR:
                IconID = BMICON_MEDIA_SD_ERROR;
            break;
            default:
                IconID = BMICON_MEDIA_SD;
            break;
        }

        if(!AHC_IsSDInserted() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
        {
            IconID = BMICON_MEDIA_NO_SD;
        }
        else if(AHC_FALSE == AHC_SDMMC_IsSD1MountDCF())
        {
            IconID = BMICON_MEDIA_NO_SD;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
#endif
}

#if (MENU_MANUAL_FOCUS_RANGE_EN && OSD_SHOW_FOCAL_RANGE)
void OSDDrawSetting_FocusRange(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    GUI_BITMAP  IconID = bmIcon_Focus_Infinity;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);//TBD
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, 0xAA000000);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiFocusRange )
        {
        #if (MENU_MANUAL_FOCUS_RANGE_MACRO_EN)
            case FOCUS_RANGE_MACRO:
                 IconID = bmIcon_Focus_Marco;
            break;
        #endif
        #if (MENU_MANUAL_FOCUS_RANGE_NORMAL_EN)
            case FOCUS_RANGE_NORMAL:
                 IconID = bmIcon_Focus_Infinity;
            break;
        #endif
            default:
                 IconID = bmIcon_Focus_Infinity;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
}
#endif

void OSDDrawSetting_SceneMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_SCENE_MODE)

    GUI_BITMAP  IconID = BMICON_UI_SCENE_AUTO;
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiScene )
        {
        #if (MENU_MANUAL_SCENE_AUTO_EN)
            case SCENE_AUTO       :
                 IconID = BMICON_UI_SCENE_AUTO;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_SPORT_EN)
            case SCENE_SPORT      :
                 IconID = BMICON_UI_SCENE_SPORT;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_PORTRAIT_EN)
            case SCENE_PORTRAIT   :
                 IconID = BMICON_UI_SCENE_PORTRAIT;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_LANDSCAPE_EN)
            case SCENE_LANDSCAPE  :
                 IconID = BMICON_UI_SCENE_LANDSCAPE;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_TWILIGHT_PORTRAIT_EN)
            case SCENE_TWILIGHT_PORTRAIT:
                 IconID = BMICON_UI_SCENE_TWILIGHT_POR;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_TWILIGHT_EN)
            case SCENE_TWILIGHT   :
                 IconID = BMICON_UI_SCENE_TWILIGHT;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_SNOW_EN)
            case SCENE_SNOW       :
                 IconID = BMICON_UI_SCENE_SNOW;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_BEACH_EN)
            case SCENE_BEACH      :
                 IconID = BMICON_UI_SCENE_BEACH;
            break;
        #endif
        #if (MENU_MANUAL_SCENE_FIREWORKS_EN)
            case SCENE_FIREWORKS  :
                 IconID = BMICON_UI_SCENE_FIREWORK;
            break;
        #endif
            default:
                 IconID = BMICON_UI_SCENE_AUTO;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_Battery(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (OSD_SHOW_BATTERY_STATUS)
    GUI_BITMAP  IconID = BMICON_BATTERY_FULL;
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+5, y+IconID.YSize+5);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,   y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, IconColor);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch (MenuSettingConfig()->uiBatteryVoltage)
        {
            case BATTERY_VOLTAGE_EMPTY:
                 IconID = BMICON_BATTERY_EXHAUST;
                 AHC_WMSG_Draw(AHC_TRUE, WMSG_LOW_BATTERY, 3);
            break;
            case BATTERY_VOLTAGE_LOW:
                 IconID = BMICON_BATTERY_EXHAUST;
            break;
            case BATTERY_VOLTAGE_LEVEL_0:
                 IconID = BMICON_BATTERY_EMPTY;
            break;
            case BATTERY_VOLTAGE_LEVEL_1:
                 IconID = BMICON_BATTERY_NORMAL;
            break;
            case BATTERY_VOLTAGE_LEVEL_2:
                 IconID = BMICON_BATTERY_MID;
            break;
            case BATTERY_VOLTAGE_FULL:
                 IconID = BMICON_BATTERY_FULL;
            break;
            default:
                 IconID = BMICON_BATTERY_FULL;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_BatteryDummy(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag)
{
#if (OSD_SHOW_BATTERY_STATUS)

    GUI_BITMAP  IconID  = BMICON_BATTERY_EMPTY;

#if (CHARGE_FULL_NOTIFY)
    extern AHC_BOOL bChargeFull;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        AHC_OSDSetColor(ubID, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);
        AHC_OSDSetBkColor(ubID, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);
    }
#endif

    switch(AHC_GetChargingID())
    {
        case 0:
            IconID = BMICON_BATTERY_EMPTY;
        break;
        case 1:
            IconID = BMICON_BATTERY_NORMAL;
        break;
        case 2:
            IconID = BMICON_BATTERY_MID;
        break;
        case 3:
            IconID = BMICON_BATTERY_FULL;
        break;
        default:
            IconID = BMICON_BATTERY_FULL;
        break;
    }

    #if (CHARGE_FULL_NOTIFY)
    if(bChargeFull)
    {
        IconID = BMICON_BATTERY_FULL;
    }
    #endif

    if(bLarge==LARGE_SIZE)
        AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
    else
        AHC_OSDDrawBitmap(ubID, &IconID, x, y);

    END_LAYER(ubID);
#endif
}

void OSDDrawSetting_BatteryStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(AHC_FALSE == AHC_Charger_GetStatus()) {
        OSDDrawSetting_Battery(ubID, x, y, bLarge, ubMag, AHC_FALSE, bkColor, NULL_PARAM);
        OSDDrawSetting_Battery(ubID, x, y, bLarge, ubMag, AHC_TRUE,  bkColor, NULL_PARAM);
    }
    else{
        if(bkColor==OSD_COLOR_TRANSPARENT) {
            BEGIN_LAYER(ubID);

            AHC_OSDSetColor(ubID, 0xAA000000);
            AHC_OSDSetBkColor(ubID, bkColor);

            END_LAYER(ubID);
        }

        OSDDrawSetting_BatteryDummy(ubID, x, y, bLarge, ubMag);
    }
}

#if (MENU_MOVIE_STABILIZE_EN && OSD_SHOW_VIDEO_STABLIZATION)
void OSDDrawSetting_VideoStablize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    GUI_BITMAP  IconID = bmIcon_ImageStable_OFF;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);//TBD
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, 0xAA000000);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiMOVStabilize )
        {
        #if (MENU_MOVIE_STABILIZE_ON_EN)
            case IMAGE_STABILIZE_ON:
                 IconID = bmIcon_ImageStable_ON;
            break;
        #endif
        #if (MENU_MOVIE_STABILIZE_OFF_EN)
            case IMAGE_STABILIZE_OFF:
                 IconID = bmIcon_ImageStable_OFF;
            break;
        #endif
            default:
                 IconID = bmIcon_ImageStable_OFF;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
}
#endif

#if (MENU_STILL_STABILIZE_EN && OSD_SHOW_IMAGE_STABLIZATION)
void OSDDrawSetting_ImageStablize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    GUI_BITMAP  IconID = bmIcon_ImageStable_OFF;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if( AHC_FALSE == bFlag )
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize+20, y+IconID.YSize+20);//TBD
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,    y+IconID.YSize);

        if(bkColor==OSD_COLOR_TRANSPARENT)
            AHC_OSDSetColor(ubID, 0xAA000000);
        else
            AHC_OSDSetColor(ubID, bkColor);
    }
    else
    {
        switch ( MenuSettingConfig()->uiIMGStabilize )
        {
        #if (MENU_STILL_STABILIZE_ON_EN)
            case IMAGE_STABILIZE_ON:
                 IconID = bmIcon_ImageStable_ON;
            break;
        #endif
        #if (MENU_STILL_STABILIZE_OFF_EN)
            case IMAGE_STABILIZE_OFF:
                 IconID = bmIcon_ImageStable_OFF;
            break;
        #endif
            default:
                 IconID = bmIcon_ImageStable_OFF;
            break;
        }

        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, &IconID, x, y);
    }

    END_LAYER(ubID);
}
#endif

void OSDDrawSetting_DriverId(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (MENU_GENERAL_DRIVER_ID_SETTING_EN && OSD_SHOW_DRIVER_ID)
    GUI_COLOR   IconColor = 0xAA000000;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    *(char *)(Driverid + 9) = '\0';

    if (AHC_CheckCurSysMode(AHC_MODE_RECORD_PREVIEW) || AHC_CheckCurSysMode(AHC_MODE_CAPTURE_PREVIEW))
    {
        if (AHC_FALSE == bFlag)
        {
            AHC_OSDSetColor(ubID, bkColor);
            AHC_OSDSetBkColor(ubID, bkColor);

            if (bLarge == LARGE_SIZE)
            {
                if (ubMag == MAG_3X)
                {
                    AHC_OSDDrawFillRect(ubID, (x - 6), (y - 6), (x + 230), (y + 38));
                }
                else if (ubMag == MAG_2X)
                {
                    AHC_OSDDrawFillRect(ubID, (x - 4), (y - 4), (x + 192), (y + 28));
                }
            }
            else
            {
                AHC_OSDDrawFillRect(ubID, (x - 2), (y - 2), (x + 118), (y + 18));
            }

            if (bkColor == OSD_COLOR_TRANSPARENT)
                AHC_OSDSetColor(ubID, IconColor);
            else
                AHC_OSDSetColor(ubID, bkColor);
        }
        else
        {
            AHC_OSDSetColor(ubID, OSD_COLOR_GREEN);
            AHC_OSDSetBkColor(ubID, bkColor);

            if (bLarge == LARGE_SIZE)
            {
                if (ubMag == MAG_3X)
                {
                    AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
                }
                else if (ubMag == MAG_2X)
                {
                    AHC_OSDSetFont(ubID, &GUI_Font24_1);
                }
            }
            else
            {
                AHC_OSDSetFont(ubID, &GUI_Font16B_1);
            }

            if (AHC_Strncmp((char *)"         ", (char *)Driverid, 9) != 0)
            {
                AHC_OSDDrawText(ubID, (UINT8 *)Driverid, x, y, 9);
            }
        }
    }

    END_LAYER(ubID);
#endif
}

void OSD_Draw_TestMessage(UINT32 Left, UINT32 Top, char result,char sText[20])
{
#ifdef CFG_DRAW_TEST_MSG //may be defined in config_xxx.h
    UINT8  bID0     = 0;
    char  sNon[]    = "";
    char  sOK[]     = " OK ";
    char  sNG[]     = " NG ";
    char  sUnDo[]   = " def ";
    char  sVer[]    = " x05 ";
    RECT  CaptureRECT = POS_BUTTON_MODESWITCH;

    CaptureRECT.uiLeft      = Left;
    CaptureRECT.uiTop       = Top;
    CaptureRECT.uiWidth     = 100;
    CaptureRECT.uiHeight    = 100;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID,  OSD_COLOR_BLUE );
    AHC_OSDSetBkColor(ubID,  OSD_COLOR_BLACK );
    AHC_OSDSetFont(ubID,  &GUI_Font13_1 );

    AHC_OSDDrawTextInRectEx(   bID0,
                               (UINT8*)sText,
                               CaptureRECT.uiLeft,
                               CaptureRECT.uiTop,
                               CaptureRECT.uiLeft + CaptureRECT.uiWidth,
                               CaptureRECT.uiTop + CaptureRECT.uiHeight,
                               GUI_TA_HCENTER | GUI_TA_VCENTER,
                               strlen(sText),
                               AHC_OSD_ROTATE_NONE );

    if(result==0)//test OK
    {
        AHC_OSDSetBkColor(ubID,  OSD_COLOR_GREEN );
        AHC_OSDDrawTextInRectEx(    bID0,
                                    (UINT8*)sOK,
                                    CaptureRECT.uiLeft+80,
                                    CaptureRECT.uiTop,
                                    CaptureRECT.uiLeft + CaptureRECT.uiWidth,
                                    CaptureRECT.uiTop + CaptureRECT.uiHeight,
                                    GUI_TA_HCENTER | GUI_TA_VCENTER,
                                    strlen(sOK),
                                    AHC_OSD_ROTATE_NONE );
    }
    else if(result==1)//test NG
    {
        AHC_OSDSetBkColor(ubID,  OSD_COLOR_RED);
        AHC_OSDDrawTextInRectEx(    bID0,
                                    (UINT8*)sNG,
                                    CaptureRECT.uiLeft+80,
                                    CaptureRECT.uiTop,
                                    CaptureRECT.uiLeft + CaptureRECT.uiWidth,
                                    CaptureRECT.uiTop + CaptureRECT.uiHeight,
                                    GUI_TA_HCENTER | GUI_TA_VCENTER,
                                    strlen(sNG),
                                    AHC_OSD_ROTATE_NONE );
    }
    else if(result==2)//default
    {
        AHC_OSDSetBkColor(ubID,  OSD_COLOR_YELLOW );
        AHC_OSDDrawTextInRectEx(    bID0,
                                    (UINT8*)sUnDo,
                                    CaptureRECT.uiLeft+80,
                                    CaptureRECT.uiTop,
                                    CaptureRECT.uiLeft + CaptureRECT.uiWidth,
                                    CaptureRECT.uiTop + CaptureRECT.uiHeight,
                                    GUI_TA_HCENTER | GUI_TA_VCENTER,
                                    strlen(sNG),
                                    AHC_OSD_ROTATE_NONE );
    }
    else if(result==3)//show version
    {
        AHC_OSDSetBkColor(ubID,  OSD_COLOR_GRAY );
        AHC_OSDDrawTextInRectEx(    bID0,
                                    (UINT8*)sVer,
                                    CaptureRECT.uiLeft+80,
                                    CaptureRECT.uiTop,
                                    CaptureRECT.uiLeft + CaptureRECT.uiWidth,
                                    CaptureRECT.uiTop + CaptureRECT.uiHeight,
                                    GUI_TA_HCENTER | GUI_TA_VCENTER,
                                    strlen(sNG),
                                    AHC_OSD_ROTATE_NONE );
    }
    else
    {
        AHC_OSDSetBkColor(ubID,  OSD_COLOR_GRAY );
        AHC_OSDDrawTextInRectEx(    bID0,
                                    (UINT8*)sNon,
                                    CaptureRECT.uiLeft+80,
                                    CaptureRECT.uiTop,
                                    CaptureRECT.uiLeft + CaptureRECT.uiWidth,
                                    CaptureRECT.uiTop + CaptureRECT.uiHeight,
                                    GUI_TA_HCENTER | GUI_TA_VCENTER,
                                    strlen(sNG),
                                    AHC_OSD_ROTATE_NONE );
    }

    END_LAYER(ubID);
#endif
}
