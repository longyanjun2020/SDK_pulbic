/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_browser.h"
#include "aihc_protection_inc.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_gui.h"
#include "ahc_menu.h"
#include "ahc_display.h"
#include "ahc_fs.h"
#include "ahc_media.h"
#include "ahc_mediaplayback.h"
#include "ahc_utility.h"
#include "ahc_warningmsg.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "keyparser.h"
#include "MenuSetting.h"
#include "statebrowserfunc.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "DrawStateMenuSetting.h"
#include "drawstatebrowserfunc.h"
#include "ColorDefine.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "ui_drawgeneral.h"
#include "OSDStrings.h"
#include "ShowOSDFunc.h"
#include "MenuStatePlaybackMenu.h"

/*===========================================================================
 * Global variable
 *===========================================================================*/

static DRAW_BROWSER_INIT_HANDLER gDrawBrowserInitHandler = DrawStateBrowserInit_Lcd;
static DRAW_BROWSER_STATE_PAGE_HANDLER gDrawBrowserStatePageHandler = DrawBrowserStatePageUpdate_Lcd;
static DRAW_BROWSER_UPDATE_HANDLER gDrawBrowserUpdateHandler = DrawStateLCDBrowserUpdate;

#if (TVOUT_ENABLE) || (HDMI_ENABLE)
UI_DARW_BROWSER_PARAMETERS m_BrowserDraw_Parameters_Active = {0};
RECT m_Browser_OsdRect = {0};
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern UINT8    m_ubBatteryStatus;
extern AHC_BOOL Deleting_InBrowser;
extern AHC_BOOL Protecting_InBrowser;
extern AHC_OSD_INSTANCE *m_OSD[];
extern AHC_BOOL m_ubPlaybackRearCam;
extern AHC_BOOL gbAhcDbgBrk;

/*===========================================================================
 * Main body
 *===========================================================================*/

void DrawBrowser_GetPageInfo(UINT16 *CurrPage, UINT16 *TotalPage)
{
    UINT32  CurrObjIdx  = 0;
    UINT32  MaxObjIdx   = 0;
    UINT32  ObjNumPerPage;
    UINT8   remains     = 0;

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    AHC_UF_GetTotalFileCount(&MaxObjIdx);
    AHC_UF_GetCurrentIndex(&CurrObjIdx);
    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }
    AHC_GetDCFObjNumPerPage(&ObjNumPerPage);

    remains = (MaxObjIdx%ObjNumPerPage)?(1):(0);

    *CurrPage  = (CurrObjIdx/ObjNumPerPage) + 1;
    *TotalPage = (MaxObjIdx/ObjNumPerPage) + remains;
}

void DrawBrowser_NameInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (BROWSER_STYLE==BROWSER_2ND_STYLE)

    UINT32      CurObjIdx;
    char        FilePathName[MAX_FULL_FILENAME_SIZE];
    UINT16      leftpos     = x;
    UINT16      WordWidth   = 8;
    char        *filename;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, 0x101010);
        AHC_OSDDrawFillRect(ubID, 195, 50, 320, 195);
    }
    else
    {
        if(bLarge==LARGE_SIZE)
        {
            if(AHC_IsTVConnectEx())
            {
                WordWidth = 14;
                AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
            }
            else if(AHC_IsHdmiConnect())
            {
                WordWidth = 16;
                AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
            }
        }
        else
        {
            WordWidth = 8;
            AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
        }

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

        {
            AHC_THUMB_CFG   ThumbConfig;
            UINT32          CurPage, ThumbPerPage, FirstObjIdx, MaxObjIdx;
            UINT32          i, y1 = 50, cnt;

            AHC_UF_GetTotalFileCount(&MaxObjIdx);

            AHC_UF_GetCurrentIndex(&CurObjIdx);

            AHC_GetThumbnailConfig(&ThumbConfig);

            if(CurObjIdx >= MaxObjIdx-1)
                CurObjIdx = MaxObjIdx-1;

            ThumbPerPage = ThumbConfig.uwTHMPerLine * ThumbConfig.uwTHMPerColume;

            CurPage = CurObjIdx / ThumbPerPage;

            FirstObjIdx = CurPage * ThumbPerPage;

            for (i = FirstObjIdx, cnt = 0; i<(CurPage+1)*ThumbPerPage && cnt<ThumbPerPage; i++, cnt++)
            {
                if(i==MaxObjIdx)
                {
                    i = 0;
                    break;
                }

                AHC_UF_SetCurrentIndex(i);
                AHC_UF_GetCurrentIndex(&i);
                if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                    AHC_UF_SetRearCamPathFlag(AHC_TRUE);
                }
                AHC_UF_GetFilePathNamebyIndex(i,FilePathName);
                filename = (char*)GetFileNameAddr(FilePathName);
                if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                    AHC_UF_SetRearCamPathFlag(AHC_FALSE);
                }

                if(i==CurObjIdx)
                    AHC_OSDSetColor(ubID, OSD_COLOR_RED);
                else
                    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);

                AHC_OSDDrawText( ubID, (UINT8*)filename, 195, y1, strlen(filename));

                y1+= 25;
            }

            AHC_UF_SetCurrentIndex(CurObjIdx);
        }

        if (Para1 != 0)
        {
            // It is for Delete/Protect/Unprotect, Show desctiption
            char    *sz;

            ShowOSD_SetLanguage(ubID);
            AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);

            sz = (char*)OSD_GetStringViaID(IDS_DS_SELECT_A_FILE);

            if(AHC_IsTVConnectEx()) {
                AHC_OSDDrawTextEx( ubID, (UINT8*)sz, leftpos-90, y, strlen(sz), 2);
            } else {
                AHC_OSDDrawText( ubID, (UINT8*)sz, leftpos,    y, strlen(sz));
            }
        }
    }

    END_LAYER(ubID);

#else

    UINT32      CurObjIdx;
    char        FilePathName[MAX_FULL_FILENAME_SIZE];
    char        DirPath[MAX_FULL_FILENAME_SIZE];
    char        *DirName;
    UINT16      leftpos     = x;
    UINT16      WordWidth   = 8;
    char        *filename;
    UINT32      uiFileNameLength;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);
        #if (TVOUT_ENABLE)
        if(AHC_IsTVConnectEx())
        {
            //avoid displaying NameInfo and DateInfo when there are no files
            AHC_OSDDrawFillRect(ubID, x-15, y, x+300, y+75);
            AHC_OSDDrawBitmapMag(ubID,
                             &bmIcon_D_Up,
                             m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset,
                             0,
                             m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize,
                             m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize);

             AHC_OSDDrawBitmapMag(ubID,
                             &bmIcon_D_Down,
                             m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset,
                             m_Browser_OsdRect.uiHeight >> 1,
                             m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize,
                             m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize);
        }
        else
        #endif
        {
            AHC_OSDDrawFillRect(ubID, x, y, x+180, y+25);
        }
    }
    else
    {
        if(bLarge==LARGE_SIZE)
        {
            if(AHC_IsTVConnectEx())
            {
                WordWidth = 14;
                AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
            }
            else if(AHC_IsHdmiConnect())
            {
                WordWidth = 16;
                AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
            }
        }
        else
        {
            WordWidth = 8;
            AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
        }

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

        if (Para1 == 0)
        {
            // For Normal Browsing page

            if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            }
            AHC_UF_GetCurrentIndex(&CurObjIdx);
            AHC_UF_GetFilePathNamebyIndex(CurObjIdx,FilePathName);
            if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                AHC_UF_SetRearCamPathFlag(AHC_FALSE);
            }
            filename = (char*)GetFileNameAddr(FilePathName);    //seperate filename from path
            uiFileNameLength = (UINT32)(filename) - (UINT32)(&FilePathName); //get the filename length

            memset(DirPath,0,sizeof(DirPath));
            memcpy(DirPath,FilePathName,uiFileNameLength-1);  //generate dirpath
            DirPath[uiFileNameLength] = '\0';
            DirName = (char*)GetFileNameAddr(DirPath);        //get dirname by dirpath

            if(JPGPB_MODE == GetCurrentOpMode())
            {
                leftpos -= 15;
            }

            AHC_OSDDrawText( ubID, (UINT8*)DirName, leftpos, y, strlen(DirName));
            leftpos += (WordWidth*strlen(DirName));
            AHC_OSDDrawText( ubID,(UINT8*)"/", leftpos, y, strlen("/"));
            leftpos += (WordWidth*1);
            AHC_OSDDrawText( ubID, (UINT8*)filename, leftpos, y, strlen(filename));
        }
        else
        {
            // It is for Delete/Protect/Unprotect, Show description of select a file
            char    *sz;

            ShowOSD_SetLanguage(ubID);
            sz = (char*)OSD_GetStringViaID(IDS_DS_SELECT_A_FILE);

            if(AHC_IsTVConnectEx()) {
                AHC_OSDDrawTextEx( ubID, (UINT8*)sz, leftpos-90, y + 4, strlen(sz), 2);
            } else {
                AHC_OSDDrawText( ubID, (UINT8*)sz, leftpos,    y, strlen(sz));
            }
        }
    }

    END_LAYER(ubID);

#endif
}

void DrawBrowser_DateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32      CurObjIdx;
    char        FilePathName[MAX_FULL_FILENAME_SIZE];
    AHC_RTC_TIME RtcTime;
    UINT16      WordWidth   = 7;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);

        #if (SUPPORT_TOUCH_PANEL)
        AHC_OSDDrawFillRect(ubID, x, y, m_OSD[ubID]->width, y+20);
        #else
        #ifdef CFG_DRAW_DATE_INFO_Y_OFFSET //may be defined in config_xxx.h
        y += CFG_DRAW_DATE_INFO_Y_OFFSET;
        #endif
        if(AHC_IsTVConnectEx())
            AHC_OSDDrawFillRect(ubID, x, y, m_OSD[ubID]->width/2, y+20);
        else
            AHC_OSDDrawFillRect(ubID, 0, y, m_OSD[ubID]->width, y+20);
        #endif
    }
    else
    {
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }
        AHC_UF_GetCurrentIndex(&CurObjIdx);
        AHC_UF_GetFilePathNamebyIndex(CurObjIdx,FilePathName);
        AHC_UF_GetFileTimebyIndex(CurObjIdx,&RtcTime);
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

#ifdef CFG_DRAW_DATE_FONT_SIZE_20 //may be defined in config_xxx.h
        WordWidth = 10;
        AHC_OSDSetFont(ubID, &GUI_Font20_ASCII);
#elif defined (CFG_DRAW_SCREEN_128) //may be defined in config_xxx.h
        WordWidth = 6;
        AHC_OSDSetFont(ubID, &GUI_Font8_ASCII);
#else
        if(bLarge==LARGE_SIZE)
        {
            WordWidth = 14;
            AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
        }
        else
        {
            WordWidth = 7;
            AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
        }
#endif
        #if (BROWSER_STYLE!=BROWSER_2ND_STYLE)
        if (Para1 != 0)
        {
            // For delete/protect/unprotect and show file name
            char        *filename;

            filename = (char*)GetFileNameAddr(FilePathName);

            if(AHC_IsTVConnectEx())
            {
                AHC_OSDDrawText(ubID, (UINT8*)filename, x-90, y + 16, strlen(filename));
                //cancel Draw_DateTime
                //x += 70;
                //OSDDraw_DateTime(ubID, x, y + 16, WordWidth, (void*)&(RtcTime.uwYear));
            }
            else
            {
            #if (SUPPORT_TOUCH_PANEL)
                AHC_OSDDrawText(ubID, (UINT8*)filename, x+10, y, strlen(filename));
            #else
                AHC_OSDDrawText(ubID, (UINT8*)filename, x, y, strlen(filename));
            #endif

                x += 150;
                OSDDraw_DateTime(ubID, x, y, WordWidth, (void*)&(RtcTime.uwYear));
            }
        }
        else
        {
            #ifdef CFG_DRAW_DATE_INFO_X //may be defined in config_xxx.h
            // x position of date/time for normal browser mode
            if (!AHC_IsTVConnectEx())
                x = 6;
            #endif
            OSDDraw_DateTime(ubID, x, y, WordWidth, (void*)&(RtcTime.uwYear));
        }
        #endif

    }

    END_LAYER(ubID);
}

void DrawHdmiBrowser_NameDateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    //char       *filename;
    UINT16       leftpos        = x;
    UINT16       WordWidth  = 16;
    UINT32       CurrentObjIdx;
    INT8         FileName[MAX_FULL_FILENAME_SIZE];
    UINT16       uwDirKey = 0;
    AHC_RTC_TIME RtcTime;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID, leftpos-90, y, leftpos+WordWidth*50, y+30);
    }
    else
    {
        if(Deleting_InBrowser || Protecting_InBrowser)
        {
            // It is for Delete/Protect/Unprotect, Show description
            char    *sz;

                AHC_OSDSetColor(ubID,OSD_COLOR_WHITE);
                AHC_OSDSetBkColor(ubID,bkColor);
                AHC_OSDSetFont(ubID,&GUI_Font32B_ASCII);

            ShowOSD_SetLanguage(ubID);
            sz = (char*)OSD_GetStringViaID(IDS_DS_SELECT_A_FILE);

            AHC_OSDDrawText( ubID, (UINT8*)sz, leftpos-90, y, strlen(sz));
        }
        else
        {
            AHC_OSDSetColor(ubID, bkColor);
            AHC_OSDDrawFillRect(ubID, leftpos-90, y, leftpos+WordWidth*50, y+30);
        }

        AHC_UF_GetCurrentIndex(&CurrentObjIdx);

        AHC_UF_GetFileNamebyIndex(CurrentObjIdx, FileName);
        AHC_UF_GetDirKeybyIndex(CurrentObjIdx, &uwDirKey);
        AHC_UF_GetFileTimebyIndex(CurrentObjIdx, &RtcTime);

        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID, leftpos, y, leftpos+WordWidth*50, y+30);
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);

        //Draw Dir Index
        AHC_OSDDrawDec(ubID, uwDirKey, leftpos,  y, 3);
        leftpos += WordWidth*4;
        AHC_OSDDrawText( ubID,(UINT8*)"-", leftpos, y, strlen("-"));

        //Draw File Name
        leftpos += WordWidth*2;
        AHC_OSDDrawText( ubID, (UINT8*)FileName, leftpos, y, strlen(FileName));

        //Draw File Date
        leftpos += WordWidth*strlen(FileName)+2;
        OSDDraw_DateTime(ubID, leftpos, y, WordWidth, (void*)&(RtcTime.uwYear));
    }

    END_LAYER(ubID);
}


#if defined(POS_BROW_RESOLUTION_SHOW)&& POS_BROW_RESOLUTION_SHOW
void DrawBrowser_ResolutionInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT8           nDigit      = 2;
    UINT16          leftpos     = x;
    UINT16          WordWidth   = 7;
    UINT32          CurObjIdx;
    UINT8           FileType;
    AHC_VIDEO_ATTR  VidInfo;
    INT32           Res_H,Res_W;
    AHC_IMG_ATTR    ImgInfo;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

#ifdef CFG_DRAW_BROWSER_IGNORE_FILE_RESOLUTION_INFO //may be defined in config_xxx.h
    /* For not to show video time */
    return;
#endif

#if (BROWSER_STYLE!=BROWSER_2ND_STYLE)
    if (Para1)
    {
        /* not to show this info in delete/protect/unprotect, due to no space */
        return;
    }
#endif

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID, x, y, m_OSD[ubID]->width, y+20);
    }
    else
    {
        AHC_UF_GetCurrentIndex(&CurObjIdx);
        AHC_UF_GetFileTypebyIndex(CurObjIdx, &FileType);

        if ( ( FileType == DCF_OBG_MOV ) ||
             ( FileType == DCF_OBG_MP4 ) ||
             ( FileType == DCF_OBG_AVI ) ||
             ( FileType == DCF_OBG_3GP ) ||
             ( FileType == DCF_OBG_TS  ) ||
             ( FileType == DCF_OBG_WMV ) )
        {
            AHC_GetVideoFileAttr(&VidInfo);

            Res_W = VidInfo.Width[0];
            Res_H = VidInfo.Height[0];
        }
        else if ( ( FileType == DCF_OBG_JPG ) ||
                  ( FileType == DCF_OBG_TIF ) )
        {
            AHC_Playback_GetImageAttr(&ImgInfo);
            Res_H = ImgInfo.ImageHSize;
            Res_W = ImgInfo.ImageVSize;
        }

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

#ifdef CFG_DRAW_DATE_FONT_SIZE_20 //may be defined in config_xxx.h
        WordWidth = 10;
        AHC_OSDSetFont(ubID, &GUI_Font20_ASCII);
#else
        if(bLarge==LARGE_SIZE)
        {
            if(AHC_IsTVConnectEx())
            {
                WordWidth = 14;
                AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
            }
            else if(AHC_IsHdmiConnect())
            {
                WordWidth = 16;
                AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
            }
        }
        else
        {
            WordWidth = 7;
            AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
        }
#endif

        AHC_OSDSetPenSize(ubID, 3);

        AHC_OSDDrawText(ubID,(UINT8*)"[", leftpos ,y-2, strlen("["));

        leftpos += WordWidth*1;
        AHC_OSDDrawDec(ubID, Res_W, leftpos, y, 4);

        leftpos += 4*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)"X", leftpos ,y, strlen("X"));

        leftpos += WordWidth+2;

        AHC_OSDDrawDec(ubID, Res_H, leftpos, y, ((Res_H >= 1000)? 4:3));

        leftpos += ((Res_H >= 1000)? 4:3)*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)"]", leftpos ,y-2, strlen("]"));
    }

    END_LAYER(ubID);
}
#endif

void DrawBrowser_TotalTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT8           nDigit      = 2;
    UINT16          leftpos     = x;
    UINT16          WordWidth   = 7;
    UINT32          CurObjIdx;
    UINT8           FileType;
    AHC_VIDEO_ATTR  VidInfo;
    AUDIO_ATTR      AudInfo;
    INT32           hour, mins, sec;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

#ifdef CFG_DRAW_BROWSER_IGNORE_VIDEO_TIME //may be defined in config_xxx.h
    /* For not to show video time */
    return;
#endif

#if (BROWSER_STYLE!=BROWSER_2ND_STYLE)
    if (Para1)
    {
        /* not to show this info in delete/protect/unprotect, due to no space */
        return;
    }
#endif

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);
        if(AHC_IsTVConnectEx())
            AHC_OSDDrawFillRect(ubID, x, y, AHC_GET_ATTR_OSD_W(ubID)/2, y+20);
        else
            AHC_OSDDrawFillRect(ubID, x, y, AHC_GET_ATTR_OSD_W(ubID)/2, y+40);
    }
    else
    {
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }
        AHC_UF_GetCurrentIndex(&CurObjIdx);
        AHC_UF_GetFileTypebyIndex(CurObjIdx, &FileType);
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }

        if ( ( FileType == DCF_OBG_MOV ) ||
             ( FileType == DCF_OBG_MP4 ) ||
             ( FileType == DCF_OBG_AVI ) ||
             ( FileType == DCF_OBG_3GP ) ||
             ( FileType == DCF_OBG_TS  ) ||
             ( FileType == DCF_OBG_WMV ) )
        {
            AHC_GetVideoFileAttr(&VidInfo);

            hour = TIME_HOUR(VidInfo.TotalTime);
            mins = TIME_MIN(VidInfo.TotalTime);
            sec  = TIME_SEC(VidInfo.TotalTime);
        }
        else if ( ( FileType == DCF_OBG_MP3 ) ||
                  ( FileType == DCF_OBG_WAV ) ||
                  ( FileType == DCF_OBG_OGG ) ||
                  ( FileType == DCF_OBG_WMA ) )
        {
            AHC_GetAudioFileAttr(&AudInfo);

            hour = TIME_HOUR(AudInfo.total_time);
            mins = TIME_MIN(AudInfo.total_time);
            sec  = TIME_SEC(AudInfo.total_time);
        }

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

#ifdef CFG_DRAW_DATE_FONT_SIZE_20 //may be defined in config_xxx.h
        WordWidth = 10;
        AHC_OSDSetFont(ubID, &GUI_Font20_ASCII);
#else
        if(bLarge==LARGE_SIZE)
        {
            if(AHC_IsTVConnectEx())
            {
                WordWidth = 14;
                AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
            }
            else if(AHC_IsHdmiConnect())
            {
                WordWidth = 16;
                AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
            }
        }
        else
        {
            WordWidth = 7;
            AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
        }
#endif

        AHC_OSDSetPenSize(ubID, 3);

        AHC_OSDDrawText(ubID,(UINT8*)"[", leftpos ,y-2, strlen("["));

        leftpos += WordWidth*1;
        AHC_OSDDrawDec(ubID, hour, leftpos, y, nDigit);

        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y-2, strlen(":"));

        leftpos += WordWidth;

        AHC_OSDDrawDec(ubID, mins, leftpos, y, nDigit);

        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y-2, strlen(":"));

        leftpos += WordWidth;
        AHC_OSDDrawDec(ubID, sec, leftpos, y, nDigit);

        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)"]", leftpos ,y-2, strlen("]"));
    }

    END_LAYER(ubID);
}

void DrawBrowser_FileInfo(UINT8 ubID)
{
    UINT32      MaxDcfObj;
    //select camID
    if(m_ubPlaybackRearCam == AHC_TRUE){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    else{
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    AHC_UF_GetTotalFileCount(&MaxDcfObj);

    if(MaxDcfObj == 0)
    {
        UIDrawEx(ubID, BROWSER_GUI_FILENAME,        AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
        UIDrawEx(ubID, BROWSER_GUI_FILE_DATE,       AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
        UIDrawEx(ubID, BROWSER_GUI_MOV_TOTAL_TIME,  AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
    }
    else
    {
        if(MOVPB_MODE == GetCurrentOpMode())
        {
            UIDrawEx(ubID, BROWSER_GUI_FILENAME,        AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
            UIDrawEx(ubID, BROWSER_GUI_FILE_DATE,       AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
            UIDrawEx(ubID, BROWSER_GUI_MOV_TOTAL_TIME,  AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
#if defined(POS_BROW_RESOLUTION_SHOW)&& POS_BROW_RESOLUTION_SHOW
            UIDrawEx(ubID, BROWSER_GUI_RESOLUTION,      AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
#endif
        }
        else if(JPGPB_MODE == GetCurrentOpMode())
        {
            UIDrawEx(ubID, BROWSER_GUI_FILENAME,        AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
            UIDrawEx(ubID, BROWSER_GUI_FILE_DATE,       AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
            UIDrawEx(ubID, BROWSER_GUI_MOV_TOTAL_TIME,  AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
#if defined(POS_BROW_RESOLUTION_SHOW)&& POS_BROW_RESOLUTION_SHOW
            UIDrawEx(ubID, BROWSER_GUI_RESOLUTION,       AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
#endif
        }
        else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
        {
            UIDrawEx(ubID, BROWSER_GUI_FILENAME,        AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
            UIDrawEx(ubID, BROWSER_GUI_FILE_DATE,       AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);
        }
    }
}

void DrawBrowser_PageInfo(UINT8 ubID)
{
#if (BROWSER_STYLE==BROWSER_2ND_STYLE)

    UINT32  CurObjIdx, MaxObjIdx;
    char    sz[20] ={0};

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    AHC_UF_GetTotalFileCount(&MaxObjIdx);
    AHC_UF_GetCurrentIndex(&CurObjIdx);

    AHC_OSDSetFont(ubID, &GUI_Font16B_1);
    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(ubID, OSD_THUMB_BACKGROUND);
    AHC_OSDSetPenSize(ubID, 1);

    if(MaxObjIdx==0)
        sprintf(sz, "%d/%d", CurObjIdx, MaxObjIdx);
    else
        sprintf(sz, "%d/%d", CurObjIdx+1, MaxObjIdx);

    AHC_OSDDrawText(ubID, (UINT8*)sz, 195, 7, sizeof(sz));

#else

    RECT    obRECT      = POS_THUMB_OBLIQUE;
    UINT16  CurrPage    = 0;
    UINT16  MaxPage     = 0;
    UINT8   digit       = 0;
    UINT16  leftpos     = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect( ubID, (POS_CURPAGE_X-POS_PAGE_OFFSET), POS_CURPAGE_Y,
                               POS_MAXPAGE_X+20,                POS_MAXPAGE_Y+16 );
    DrawBrowser_GetPageInfo(&CurrPage, &MaxPage);

    AHC_OSDSetFont(ubID, &GUI_Font16B_1);
    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(ubID, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetPenSize(ubID, 1);

    if(0 != MaxPage)
    {
        digit = NumOfDigit(MaxPage);
        leftpos = POS_PAGEINFO(digit, POS_CURPAGE_X);
        AHC_OSDDrawDec( ubID, CurrPage, leftpos,  POS_CURPAGE_Y, digit);

        leftpos = POS_PAGEINFO(digit, POS_MAXPAGE_X);
        AHC_OSDDrawDec( ubID, MaxPage, leftpos,  POS_MAXPAGE_Y, digit );

        AHC_OSDSetPenSize(ubID, 3);

        AHC_OSDDrawLine( ubID, obRECT.uiLeft, obRECT.uiLeft+obRECT.uiWidth, obRECT.uiTop, obRECT.uiTop-obRECT.uiHeight);
    }
    else
    {   // one page
        leftpos = POS_PAGEINFO(digit, POS_CURPAGE_X);
        AHC_OSDDrawDec( ubID, 0, leftpos,  POS_CURPAGE_Y, 1);

        leftpos = POS_PAGEINFO(digit, POS_MAXPAGE_X);
        AHC_OSDDrawDec( ubID, 0, leftpos,  POS_MAXPAGE_Y, 1);

        AHC_OSDSetPenSize(ubID, 3);

        AHC_OSDDrawLine( ubID, obRECT.uiLeft, obRECT.uiLeft+obRECT.uiWidth, obRECT.uiTop, obRECT.uiTop-obRECT.uiHeight);
    }
#endif

    END_LAYER(ubID);
}
#if (HDMI_ENABLE)
void DrawHdmiBrowser_PageInfo(UINT8 ubID)
{
    UINT16  CurrPage    = 0;
    UINT16  MaxPage     = 0;
    UINT8   digit       = 0;
    UINT16  leftpos     = 0;
    UINT16  tempOffset  = 55;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, OSD_COLOR_TITLE);

    tempOffset = m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset;

    AHC_OSDDrawFillRect(ubID,
        m_BrowserDraw_Parameters_Active.guwBrowserRectUpLeftX + tempOffset,
        m_BrowserDraw_Parameters_Active.guwBrowserRectUpLeftY,
        m_BrowserDraw_Parameters_Active.guwBrowserRectLowRightX + tempOffset,
        m_BrowserDraw_Parameters_Active.guwBrowserRectLowRightY);

    DrawBrowser_GetPageInfo(&CurrPage, &MaxPage);

    if(0 != MaxPage)
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, OSD_COLOR_TITLE);
        AHC_OSDSetFont(ubID, &GUI_Font32B_ASCII);
        AHC_OSDSetPenSize(ubID, 3);

        digit = NumOfDigit(MaxPage);

        leftpos = POS_PAGEINFO(digit, m_BrowserDraw_Parameters_Active.guwBrowserOffsetPos1 + tempOffset);

        AHC_OSDDrawDec(ubID,
                        CurrPage,
                        leftpos,
                        m_BrowserDraw_Parameters_Active.guwBrowserDecY1,
                        digit);

        leftpos = POS_PAGEINFO(digit, m_BrowserDraw_Parameters_Active.guwBrowserOffsetPos2 + tempOffset);

        AHC_OSDDrawDec(ubID,
                        MaxPage,
                        leftpos,
                        m_BrowserDraw_Parameters_Active.guwBrowserDecY2,
                        digit);

        AHC_OSDDrawLine(ubID,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineStartX + tempOffset,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineStartY + tempOffset,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineEndX,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineEndY);
    }

    END_LAYER(ubID);
}
#endif
#if (TVOUT_ENABLE)
void DrawTVBrowser_PageInfo(UINT8 ubID)
{
    UINT16  CurrPage    = 0;
    UINT16  MaxPage     = 0;
    UINT8   digit       = 0;
    UINT16  leftpos     = 0;
    UINT16  tempOffset  = 20;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    if(Deleting_InBrowser || Protecting_InBrowser)
        return;

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, OSD_COLOR_TITLE);

    tempOffset = m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset;

    AHC_OSDDrawFillRect(ubID,
        m_BrowserDraw_Parameters_Active.guwBrowserRectUpLeftX + tempOffset,
        m_BrowserDraw_Parameters_Active.guwBrowserRectUpLeftY,
        m_BrowserDraw_Parameters_Active.guwBrowserRectLowRightX + tempOffset,
        m_BrowserDraw_Parameters_Active.guwBrowserRectLowRightY);

    DrawBrowser_GetPageInfo(&CurrPage, &MaxPage);

    if(0 != MaxPage)
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, OSD_COLOR_TITLE);
        AHC_OSDSetFont(ubID, &GUI_Font16B_1);
        AHC_OSDSetPenSize(ubID, 2);

        digit = NumOfDigit(MaxPage);

        leftpos = POS_PAGEINFO(digit, m_BrowserDraw_Parameters_Active.guwBrowserOffsetPos1 + tempOffset);

        AHC_OSDDrawDec(ubID,
                        CurrPage,
                        leftpos,
                        m_BrowserDraw_Parameters_Active.guwBrowserDecY1,
                        digit);

        leftpos = POS_PAGEINFO(digit, m_BrowserDraw_Parameters_Active.guwBrowserOffsetPos2 + tempOffset);

        AHC_OSDDrawDec(ubID,
                        MaxPage,
                        leftpos,
                        m_BrowserDraw_Parameters_Active.guwBrowserDecY2,
                        digit);

        AHC_OSDDrawLine(ubID,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineStartX + tempOffset,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineStartY + tempOffset,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineEndX,
                        m_BrowserDraw_Parameters_Active.guwBrowserLineEndY);
    }

    END_LAYER(ubID);
}
#endif

void DrawBrowser_BackCurtain(UINT8 ulID)
{
    UINT16 osdW;
    UINT16 osdH;
    osdW = AHC_GET_ATTR_OSD_W(ulID);
    osdH = AHC_GET_ATTR_OSD_H(ulID);

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ulID);

    AHC_OSDSetColor(ulID, OSD_COLOR_TITLE);
    AHC_OSDDrawFillRect( ulID, 0, 0,                          BG_CURTAIN_W, BG_CURTAIN_H);
    AHC_OSDDrawFillRect( ulID, 0, (DISP_HEIGHT-BG_CURTAIN_H), BG_CURTAIN_W, DISP_HEIGHT );

    AHC_OSDSetColor(ulID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect( ulID, 0, BG_CURTAIN_H+BG_CURTAIN_EDGE, BG_CURTAIN_W, DISP_HEIGHT-BG_CURTAIN_H-BG_CURTAIN_EDGE  );

    AHC_OSDSetPenSize(ulID, 5);
    AHC_OSDSetColor(ulID, OSD_COLOR_WHITE);
    AHC_OSDDrawFillRect( ulID, 0, BG_CURTAIN_H,                               osdW, BG_CURTAIN_H+BG_CURTAIN_EDGE);
    AHC_OSDDrawFillRect(ulID, 0, osdH-BG_CURTAIN_H-BG_CURTAIN_EDGE, osdW, osdH-BG_CURTAIN_H);
    END_LAYER(ulID);
}

void DrawBrowser_SwitchMode_Lcd(UINT8 ulID, OP_MODE_SETTING OpMode)
{
    RECT  mRECT  = POS_BUTTON_MENU_2;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ulID);

    AHC_OSDSetColor(ulID, OSD_COLOR_TITLE);

    AHC_OSDDrawFillRect2(ulID, &mRECT);

    if(MOVPB_MODE == OpMode)
    {
        AHC_OSDDrawBitmap(ulID, &BMICON_BUTTON_MOVIE, mRECT.uiLeft, mRECT.uiTop);
        END_LAYER(ulID);
    }
    else if(JPGPB_MODE == OpMode)
    {
        AHC_OSDDrawBitmap(ulID, &BMICON_BUTTON_STILL, mRECT.uiLeft, mRECT.uiTop);
        END_LAYER(ulID);
        UIDrawEx(ulID, BROWSER_GUI_MOV_TOTAL_TIME, AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, NULL);
    }
}

#if (HDMI_ENABLE)
void DrawBrowser_SwitchMode_Hdmi(UINT8 ulID, OP_MODE_SETTING OpMode)
{
    UINT16  ulIconX, ulIconY;
    UINT8   ulMagSize;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    BEGIN_LAYER(ulID);

    AHC_OSDSetColor(ulID, OSD_COLOR_TITLE);


    ulIconX     = m_BrowserDraw_Parameters_Active.guwBrowserIconX;
    ulIconY     = m_BrowserDraw_Parameters_Active.guwBrowserIconY;
    ulMagSize   = m_BrowserDraw_Parameters_Active.gubBrowserMagSize;

    AHC_OSDDrawFillRect(ulID,
                ulIconX,
                ulIconY,
                ulIconX + m_BrowserDraw_Parameters_Active.guwBrowserIconOffsetX,
                ulIconY + m_BrowserDraw_Parameters_Active.guwBrowserIconOffsetY);

    if(MOVPB_MODE == OpMode)
    {
        AHC_OSDDrawBitmapMag(ulID, &bmIcon_Movie_Playback, ulIconX, ulIconY, ulMagSize, ulMagSize);
    }
    else if(JPGPB_MODE == OpMode)
    {
        AHC_OSDDrawBitmapMag(ulID, &bmIcon_Still_Playback, ulIconX, ulIconY, ulMagSize, ulMagSize);
        //UIDrawEx(ulID, BROWSER_GUI_MOV_TOTAL_TIME, AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, Deleting_InBrowser || Protecting_InBrowser);//
    }

    END_LAYER(ulID);
}
#endif

#if (TVOUT_ENABLE)
void DrawBrowser_SwitchMode_Tv(UINT8 ulID, OP_MODE_SETTING OpMode)
{
    UINT16  ulIconX, ulIconY;
    UINT8   ulMagSize;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    BEGIN_LAYER(ulID);

    AHC_OSDSetColor(ulID, OSD_COLOR_TITLE);

    ulIconX     = m_BrowserDraw_Parameters_Active.guwBrowserIconX;
    ulIconY     = m_BrowserDraw_Parameters_Active.guwBrowserIconY;
    ulMagSize   = m_BrowserDraw_Parameters_Active.gubBrowserMagSize;

    AHC_OSDDrawFillRect(ulID,
                ulIconX,
                ulIconY,
                ulIconX + m_BrowserDraw_Parameters_Active.guwBrowserIconOffsetX,
                ulIconY + m_BrowserDraw_Parameters_Active.guwBrowserIconOffsetY);

    if(MOVPB_MODE == OpMode)
    {
        AHC_OSDDrawBitmapMag(ulID, &bmIcon_Movie_Playback, ulIconX, ulIconY, ulMagSize, ulMagSize);
        END_LAYER(ulID);
    }
    else if(JPGPB_MODE == OpMode)
    {
        AHC_OSDDrawBitmapMag(ulID, &bmIcon_Still_Playback, ulIconX, ulIconY, ulMagSize, ulMagSize);
        END_LAYER(ulID);

//        DrawTVBrowser_TotalTime(ulID, ulTimeX, ulTimeY, LARGE_SIZE, MAG_2X, AHC_FALSE, OSD_COLOR_TITLE, NULL_PARAM);
        UIDrawEx(ulID, BROWSER_GUI_MOV_TOTAL_TIME,  AHC_TRUE, AHC_FALSE, OSD_COLOR_TITLE, NULL_PARAM);
    }
}
#endif

void DrawStateBrowserInit_Lcd(void)
{
    UINT8  bID0     = 0;
    UINT8  bID1     = 0;
#if (BROWSER_STYLE!=BROWSER_2ND_STYLE)
    RECT   uRECT    = POS_THUMB_PGUP;
    RECT   dRECT    = POS_THUMB_PGDOWN;
#endif
#if (SUPPORT_TOUCH_PANEL)
    RECT   mRECT    = RECT_TOUCH_BUTTON_BRO_MENU;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    CHARGE_ICON_ENABLE(AHC_FALSE);

    OSDDraw_EnterDrawing(&bID0, &bID1);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    BEGIN_LAYER(bID0);
    OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
    END_LAYER(bID0);

    BEGIN_LAYER(bID1);
    OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);
    END_LAYER(bID1);

    DrawBrowser_BackCurtain(bID0);

#if (BROWSER_STYLE!=BROWSER_2ND_STYLE)
    BEGIN_LAYER(bID0);
    AHC_OSDDrawBitmap(bID0, &bmIcon_D_Up,   uRECT.uiLeft, uRECT.uiTop);
    AHC_OSDDrawBitmap(bID0, &bmIcon_D_Down, dRECT.uiLeft, dRECT.uiTop);
    END_LAYER(bID0);
#endif

#if (SUPPORT_TOUCH_PANEL)
    BEGIN_LAYER(bID0);
    AHC_OSDDrawBitmap(bID0, &bmIcon_Menu,   mRECT.uiLeft, mRECT.uiTop);
    OSD_ShowStringPool3(bID0, IDS_DS_MENU, mRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_HCENTER|GUI_TA_VCENTER);
    END_LAYER(bID0);
#endif

    DrawBrowser_SwitchMode_Lcd(bID0, GetCurrentOpMode());

    DrawBrowser_PageInfo(bID0);

    DrawBrowser_FileInfo(bID0);

    UIDrawEx(bID0, BROWSER_GUI_UI_MODE,     AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);

    UIDrawEx(bID0, BROWSER_GUI_SD_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);

    UIDrawEx(bID0, BROWSER_GUI_BATTERY,     AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);

    OSDDraw_ExitDrawing(&bID0, &bID1);

    CHARGE_ICON_ENABLE(AHC_TRUE);
}

#if (HDMI_ENABLE)
void DrawStateBrowserInit_Hdmi(void)
{
    UINT8   bID0        = 0;
    UINT8   bID1        = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

#if (POWER_OFF_CONFIRM_PAGE_EN)
    if(PowerOff_InProcess)
    {
        OSDDraw_EnterDrawing(&bID0, &bID1);
        OSDDraw_ClearOvlDrawOvlBufferAll();
        MenuDrawSubPage_PowerOff_HDMI_Browser(bID0);
        PowerOff_Option  = CONFIRM_OPT_YES;
        OSDDraw_ExitDrawing(&bID0, &bID1);
        return;
    }
#endif

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TITLE);

    AHC_OSDDrawFillRect(bID0, 0, 0, m_Browser_OsdRect.uiLeft+m_Browser_OsdRect.uiWidth, m_Browser_OsdRect.uiTop+m_Browser_OsdRect.uiHeight);
    AHC_OSDDrawBitmapMag(bID0,
                    &bmIcon_D_Up,
                    m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset,
                    0,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize);

    AHC_OSDDrawBitmapMag(bID0,
                    &bmIcon_D_Down,
                    m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset,
                    m_Browser_OsdRect.uiHeight >> 1,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize);

    END_LAYER(bID0);

    DrawBrowser_SwitchMode_Hdmi(bID0, GetCurrentOpMode());

    DrawHdmiBrowser_PageInfo(bID0);

    DrawBrowser_FileInfo(bID0);

    UIDrawEx(bID0, BROWSER_GUI_SD_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);//    DrawHdmiBrowser_MediaType(bID0, AHC_TRUE);

    UIDrawEx(bID0, BROWSER_GUI_BATTERY, AHC_FALSE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);//    DrawHdmiBrowser_Battery(bID0, AHC_TRUE);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetPenSize(bID0, 3);

    AHC_OSDDrawLine(bID0, 0, m_Browser_OsdRect.uiWidth-3, m_Browser_OsdRect.uiHeight-3, m_Browser_OsdRect.uiHeight-3);

    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif

#if (TVOUT_ENABLE)
void DrawStateBrowserInit_Tv(void)
{
    UINT8  bID0         = 0;
    UINT8  bID1         = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

#if (POWER_OFF_CONFIRM_PAGE_EN)
    if(PowerOff_InProcess)
    {
        OSDDraw_EnterDrawing(&bID0, &bID1);
        OSDDraw_ClearOvlDrawOvlBufferAll();
        MenuDrawSubPage_PowerOff_TV_Browser(bID0);
        PowerOff_Option  = CONFIRM_OPT_YES;
        OSDDraw_ExitDrawing(&bID0, &bID1);
        return;
    }
#endif

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TITLE);

    AHC_OSDDrawFillRect(bID0, 0, 0, m_Browser_OsdRect.uiLeft+m_Browser_OsdRect.uiWidth, m_Browser_OsdRect.uiTop+m_Browser_OsdRect.uiHeight);
    AHC_OSDDrawBitmapMag(bID0,
                    &bmIcon_D_Up,
                    m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset,
                    0,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize);

    AHC_OSDDrawBitmapMag(bID0,
                    &bmIcon_D_Down,
                    m_BrowserDraw_Parameters_Active.guwBrowserCommonOffset,
                    m_Browser_OsdRect.uiHeight >> 1,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize,
                    m_BrowserDraw_Parameters_Active.gubBrowserBitmapMagSize);


    END_LAYER(bID0);

    DrawBrowser_SwitchMode_Tv(bID0, GetCurrentOpMode());

    DrawBrowser_FileInfo(bID0);

    DrawTVBrowser_PageInfo(bID0);

//  OSDDrawSetting_MediaType(bID0, ulMediaX, ulMediaY, LARGE_SIZE, MAG_2X, AHC_TRUE,  OSD_COLOR_TITLE, NULL_PARAM);
    UIDrawEx(bID0, BROWSER_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);

//    OSDDrawSetting_BatteryStatus(bID0, ulBattX, ulBattY, LARGE_SIZE, MAG_2X, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    UIDrawEx(bID0, BROWSER_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetPenSize(bID0, 2);
    AHC_OSDDrawLine(bID0, 0, m_Browser_OsdRect.uiWidth-2, m_Browser_OsdRect.uiHeight-2, m_Browser_OsdRect.uiHeight-2);

    OSDDraw_ExitDrawing(&bID0, &bID1);
    END_LAYER(bID0);
    AHC_OSDSetActive(bID0, 1);
    AHC_OSDSetActive(bID1, 1);
}
#endif

void DrawStateBrowserInit(void)
{
    if(NULL != gDrawBrowserInitHandler){
        gDrawBrowserInitHandler();
    }
}

void DrawStateBrowserSwitch_Lcd(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    AHC_OSDSetColor(bID0, 0xAA000000);

    DrawBrowser_SwitchMode_Lcd(bID0, GetCurrentOpMode());

    UIDrawEx(bID0, BROWSER_GUI_UI_MODE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);
    UIDrawEx(bID0, BROWSER_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TITLE, NULL_PARAM);

    DrawBrowser_PageInfo(bID0);

    DrawBrowser_FileInfo(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

#if (HDMI_ENABLE)
void DrawStateBrowserSwitch_Hdmi(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    AHC_OSDSetColor(bID0, 0xAA000000);

    DrawBrowser_SwitchMode_Hdmi(bID0, GetCurrentOpMode());
    DrawHdmiBrowser_PageInfo(bID0);
    DrawBrowser_FileInfo(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif

#if (TVOUT_ENABLE)
void DrawStateBrowserSwitch_Tv(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, 0xAA000000);

    END_LAYER(bID0);

    DrawBrowser_SwitchMode_Tv(bID0, GetCurrentOpMode());

    DrawTVBrowser_PageInfo(bID0);

    DrawBrowser_FileInfo(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
    AHC_OSDSetActive(bID0, 1);
    AHC_OSDSetActive(bID1, 1);
}
#endif

void DrawBrowserStatePageUpdate_Lcd(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, 0xAA000000);

    END_LAYER(bID0);

    DrawBrowser_PageInfo(bID0);

    DrawBrowser_FileInfo(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

#if (HDMI_ENABLE)
void DrawBrowserStatePageUpdate_Hdmi(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    AHC_OSDSetColor(bID0, 0xAA000000);

    DrawHdmiBrowser_PageInfo(bID0);
    DrawBrowser_FileInfo(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif

#if (TVOUT_ENABLE)
void DrawBrowserStatePageUpdate_Tv(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, 0xAA000000);

    END_LAYER(bID0);

    DrawBrowser_FileInfo(bID0);

    DrawTVBrowser_PageInfo(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
    AHC_OSDSetActive(bID0, 1);
    AHC_OSDSetActive(bID1, 1);
}
#endif

void DrawBrowserStatePageUpdate(void)
{
    if(NULL != gDrawBrowserStatePageHandler){
        gDrawBrowserStatePageHandler();
    }
}

void DrawBrowserStateSDMMC_In(void)
{
    MenuStatePlaybackSelectDB(GetCurrentOpMode());
    BrowserFunc_DisplaySetting();
//  BrowserFunc_CheckLCDstatus();
    DrawStateBrowserInit();
}

void DrawBrowserStateSDMMC_Out(void)
{
    DrawStateBrowserInit();
    printc("Clear Browser when SDMMC OUT\r\n");
}

void DrawBrowserStatePlaybackRearCam( AHC_BOOL bEnable )
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    RECT   rtIconPosition = { STRETCH_W(40), STRETCH_H(176), 60, 20 };

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    if( bEnable == AHC_TRUE ){
        AHC_OSDSetFont(bID0, &GUI_Font16B_1);

        OSD_ShowString(bID0, (char*)"RearCam", NULL, rtIconPosition, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_LEFT|GUI_TA_VCENTER);
        //AHC_OSDDrawBitmap(bID0, &bmIcon_Scene_Auto, rtIconPosition.uiLeft, rtIconPosition.uiTop);
    }
    else{
        AHC_OSDSetColor( bID0, OSD_COLOR_TRANSPARENT );
        AHC_OSDSetBkColor( bID0, OSD_COLOR_TRANSPARENT );

        AHC_OSDDrawFillRect(bID0, rtIconPosition.uiLeft, rtIconPosition.uiTop, rtIconPosition.uiLeft+rtIconPosition.uiWidth, rtIconPosition.uiTop+rtIconPosition.uiHeight);
    }

    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

void DrawBrowserStateClearOSD(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);

    DrawBrowser_BackCurtain(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStateLCDBrowserUpdate(UINT32 ubEvent)
{
    switch(ubEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_UP                         :
        case EVENT_KEY_DOWN                       :
        case EVENT_KEY_LEFT                       :
        case EVENT_KEY_RIGHT                      :
        case EVENT_THUMBNAIL_KEY_PAGE_UP:
        case EVENT_THUMBNAIL_KEY_PAGE_DOWN:
        case EVENT_THUMBNAIL_KEY_PAGE_UPDATE:
            DrawBrowserStatePageUpdate();
        break;

        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
            DrawStateBrowserInit();
            AHC_Thumb_DrawPage(AHC_TRUE);

            if (GetCurrentOpMode() == MOVPB_MODE)
            {
                AHC_UF_SetRearCamPathFlag(m_ubPlaybackRearCam);
                DrawBrowserStatePlaybackRearCam( m_ubPlaybackRearCam );
            }
        break;

        case EVENT_THUMBNAIL_MODE_INIT            :
            DrawStateBrowserInit();

            if (GetCurrentOpMode() == MOVPB_MODE|| GetCurrentOpMode() == JPGPB_MODE)
            {
                AHC_UF_SetRearCamPathFlag(m_ubPlaybackRearCam);
                DrawBrowserStatePlaybackRearCam( m_ubPlaybackRearCam );
            }
            else
                DrawBrowserStatePlaybackRearCam( AHC_FALSE );
        break;

        case EVENT_THUMBNAIL_MODE                 :
            DrawStateBrowserSwitch_Lcd();//DrawStateBrowserSwitch();
        break;

        case EVENT_THUMBNAIL_MODE_CLEAR_OSD   :
            DrawBrowserStateClearOSD();
        break;

        case EVENT_THUMBNAIL_UPDATE_MESSAGE       :
        break;

        default:
        break;
    }
}

#if (HDMI_ENABLE)
void DrawStateHdmiBrowserUpdate(UINT32 ulEvent)
{
    //OSDDraw_EnterDrawing(&bID0, &bID1);

    switch( ulEvent )
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_MODE                       :
        case EVENT_THUMBNAIL_MODE                   :
            DrawStateBrowserSwitch_Hdmi();//DrawStateBrowserSwitch();
        break;
        case EVENT_THUMBNAIL_MODE_CLEAR_OSD     :
            DrawBrowserStateClearOSD();
        break;
        case EVENT_KEY_UP                         :
        case EVENT_KEY_DOWN                       :
        case EVENT_KEY_LEFT                       :
        case EVENT_KEY_RIGHT                      :
        case EVENT_HDMI_BROWSER_KEY_PAGE_UP       :
        case EVENT_HDMI_BROWSER_KEY_PAGE_DOWN     :
            DrawBrowserStatePageUpdate();
            //AHC_OSDSetActive(bID0, 1);
            //AHC_OSDSetActive(bID1, 1);
        break;

        case EVENT_THUMBNAIL_MODE_INIT            :
        case EVENT_HDMI_CHANGE_MODE_INIT          :
            {
                //AHC_OSDSetActive(bID0, 0);
                //AHC_OSDSetActive(bID1, 0);
                DrawStateBrowserInit();
                //AHC_OSDSetActive(bID0, 1);
                //AHC_OSDSetActive(bID1, 1);
            }
        break;

        default:
        break;
    }

    //OSDDraw_ExitDrawing(&bID0, &bID1);

}
#endif

#if (TVOUT_ENABLE)
void DrawStateTVBrowserUpdate(UINT32 ulEvent)
{
    switch( ulEvent )
    {
        case EVENT_NONE                           :
        break;

        case EVENT_THUMBNAIL_MODE                   :
        case EVENT_KEY_MODE                       :
        case EVENT_KEY_NEXT_MODE:
        case EVENT_KEY_PREV_MODE:
            DrawStateBrowserSwitch_Tv();//DrawStateBrowserSwitch();
        break;
        case EVENT_THUMBNAIL_MODE_CLEAR_OSD     :
            DrawBrowserStateClearOSD();
        break;

        case EVENT_KEY_UP                         :
        case EVENT_KEY_DOWN                       :
        case EVENT_KEY_LEFT                       :
        case EVENT_KEY_RIGHT                      :
        case EVENT_TV_BROWSER_KEY_PAGE_UP         :
        case EVENT_TV_BROWSER_KEY_PAGE_DOWN       :
            DrawBrowserStatePageUpdate();
        break;

        case EVENT_THUMBNAIL_MODE_INIT          :
        case EVENT_TV_CHANGE_MODE_INIT          :
            DrawStateBrowserInit();
        break;
        case EVENT_PARKING_KEY:
            DrawBrowserStatePageUpdate();
            break;
        default:
        break;
    }
}
#endif

void DrawStateNoPanelBrowserUpdate(UINT32 ulEvent)
{
    //TBD
}
void DrawStateBrowserUpdate(UINT32 ubEvent)
{
    if(NULL != gDrawBrowserUpdateHandler){
        gDrawBrowserUpdateHandler(ubEvent);
    }
}

void DrawBrowserStateFunctionSelectLCD(void)
{
    gDrawBrowserInitHandler = DrawStateBrowserInit_Lcd;
    gDrawBrowserStatePageHandler = DrawBrowserStatePageUpdate_Lcd;
    gDrawBrowserUpdateHandler = DrawStateLCDBrowserUpdate;
}

#if (HDMI_ENABLE)
void DrawBrowserStateFunctionSelectHDMI(void)
{
    gDrawBrowserInitHandler = DrawStateBrowserInit_Hdmi;
    gDrawBrowserStatePageHandler = DrawBrowserStatePageUpdate_Hdmi;
    gDrawBrowserUpdateHandler = DrawStateHdmiBrowserUpdate;

    switch(MenuSettingConfig()->uiHDMIOutput)
    {
#if MENU_GENERAL_HDMI_OUTPUT_1080I_EN
        case HDMI_OUTPUT_1080I:
            {
                UI_DARW_BROWSER_PARAMETERS sBrowserDraw_Hdmi_Parameters_1080I = UI_DARW_BROWSER_HDMI_1080I_PARAMETERS;

                m_Browser_OsdRect.uiLeft        = POS_HDMI_1080I_BROWSER_OSD_X0;
                m_Browser_OsdRect.uiTop         = POS_HDMI_1080I_BROWSER_OSD_Y0;
                m_Browser_OsdRect.uiWidth   = POS_HDMI_1080I_BROWSER_OSD_W;
                m_Browser_OsdRect.uiHeight  = POS_HDMI_1080I_BROWSER_OSD_H;

                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosX  = POS_HDMI_1080I_BRO_BATT_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosY  = POS_HDMI_1080I_BRO_BATT_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_ubMag = MAG_4X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosX     = POS_HDMI_1080I_BRO_MEDIA_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosY     = POS_HDMI_1080I_BRO_MEDIA_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_ubMag    = MAG_4X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosX   = POS_HDMI_1080I_BRO_TOTALTIME_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosY   = POS_HDMI_1080I_BRO_TOTALTIME_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_ubMag  = MAG_4X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosX = POS_HDMI_1080I_BRO_NAMEDATE_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosY = POS_HDMI_1080I_BRO_NAMEDATE_Y;

                m_BrowserDraw_Parameters_Active = sBrowserDraw_Hdmi_Parameters_1080I;
            }
            break;
#endif

#if MENU_GENERAL_HDMI_OUTPUT_720P_EN
        case HDMI_OUTPUT_720P:
            {
                UI_DARW_BROWSER_PARAMETERS sBrowserDraw_Hdmi_Parameters_720P = UI_DARW_BROWSER_HDMI_720P_PARAMETERS;

                m_Browser_OsdRect.uiLeft        = POS_HDMI_720P_BROWSER_OSD_X0;
                m_Browser_OsdRect.uiTop         = POS_HDMI_720P_BROWSER_OSD_Y0;
                m_Browser_OsdRect.uiWidth   = POS_HDMI_720P_BROWSER_OSD_W;
                m_Browser_OsdRect.uiHeight  = POS_HDMI_720P_BROWSER_OSD_H;

                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosX  = POS_HDMI_720P_BRO_BATT_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosY  = POS_HDMI_720P_BRO_BATT_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_ubMag = MAG_3X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosX     = POS_HDMI_720P_BRO_MEDIA_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosY     = POS_HDMI_720P_BRO_MEDIA_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_ubMag    = MAG_3X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosX   = POS_HDMI_720P_BRO_TOTALTIME_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosY   = POS_HDMI_720P_BRO_TOTALTIME_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_ubMag  = MAG_3X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosX = POS_HDMI_720P_BRO_NAMEDATE_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosY = POS_HDMI_720P_BRO_NAMEDATE_Y;

                m_BrowserDraw_Parameters_Active = sBrowserDraw_Hdmi_Parameters_720P;
            }
            break;
#endif

#if MENU_GENERAL_HDMI_OUTPUT_480P_EN
        case HDMI_OUTPUT_480P:
            {
                UI_DARW_BROWSER_PARAMETERS sBrowserDraw_Hdmi_Parameters_480P = UI_DARW_BROWSER_HDMI_480P_PARAMETERS;

                m_Browser_OsdRect.uiLeft        = POS_HDMI_480P_BROWSER_OSD_X0;
                m_Browser_OsdRect.uiTop         = POS_HDMI_480P_BROWSER_OSD_Y0;
                m_Browser_OsdRect.uiWidth   = POS_HDMI_480P_BROWSER_OSD_W;
                m_Browser_OsdRect.uiHeight  = POS_HDMI_480P_BROWSER_OSD_H;

                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosX  = POS_HDMI_720P_BRO_BATT_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosY  = POS_HDMI_720P_BRO_BATT_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_ubMag = MAG_2X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosX     = POS_HDMI_720P_BRO_MEDIA_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosY     = POS_HDMI_720P_BRO_MEDIA_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_ubMag    = MAG_2X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosX       = POS_HDMI_480P_BRO_TOTALTIME_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosY       = POS_HDMI_480P_BRO_TOTALTIME_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_ubMag      = MAG_3X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosX = POS_HDMI_480P_BRO_NAMEDATE_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosY = POS_HDMI_480P_BRO_NAMEDATE_Y;

                m_BrowserDraw_Parameters_Active = sBrowserDraw_Hdmi_Parameters_480P;
            }
            break;
#endif

        default:
#if MENU_GENERAL_HDMI_OUTPUT_1080P_EN
        case HDMI_OUTPUT_1080P:
#endif
            {
                UI_DARW_BROWSER_PARAMETERS sBrowserDraw_Hdmi_Parameters_1080P = UI_DARW_BROWSER_HDMI_1080P_PARAMETERS;

                m_Browser_OsdRect.uiLeft        = POS_HDMI_1080P_BROWSER_OSD_X0;
                m_Browser_OsdRect.uiTop         = POS_HDMI_1080P_BROWSER_OSD_Y0;
                m_Browser_OsdRect.uiWidth   = POS_HDMI_1080P_BROWSER_OSD_W;
                m_Browser_OsdRect.uiHeight  = POS_HDMI_1080P_BROWSER_OSD_H;

                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosX  = POS_HDMI_1080P_BRO_BATT_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_PosY  = POS_HDMI_1080P_BRO_BATT_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_BATTERY].m_ubMag     = MAG_4X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosX     = POS_HDMI_1080P_BRO_MEDIA_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_PosY = POS_HDMI_1080P_BRO_MEDIA_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_SD_STATE].m_ubMag    = MAG_4X;


                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosX       = POS_HDMI_1080P_BRO_TOTALTIME_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_PosY       = POS_HDMI_1080P_BRO_TOTALTIME_Y;
                m_BrowserDraw_Hdmi[BROWSER_GUI_MOV_TOTAL_TIME].m_ubMag      = MAG_4X;

                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosX = POS_HDMI_1080P_BRO_NAMEDATE_X;
                m_BrowserDraw_Hdmi[BROWSER_GUI_FILENAME].m_PosY = POS_HDMI_1080P_BRO_NAMEDATE_Y;

                m_BrowserDraw_Parameters_Active = sBrowserDraw_Hdmi_Parameters_1080P;
            }
            break;
    }

}
#endif

#if (TVOUT_ENABLE)
void DrawBrowserStateFunctionSelectTv(void)
{
    gDrawBrowserInitHandler = DrawStateBrowserInit_Tv;
    gDrawBrowserStatePageHandler = DrawBrowserStatePageUpdate_Tv;
    gDrawBrowserUpdateHandler = DrawStateTVBrowserUpdate;

    switch(MenuSettingConfig()->uiTVSystem)
    {
        case TV_SYSTEM_NTSC:
            {
                UI_DARW_BROWSER_PARAMETERS sBrowserDraw_Hdmi_Parameters_NTSC = UI_DARW_BROWSER_TV_NTSC_PARAMETERS;

                m_Browser_OsdRect.uiLeft        = POS_TV_NTSC_BROWSER_OSD_X0;
                m_Browser_OsdRect.uiTop         = POS_TV_NTSC_BROWSER_OSD_Y0;
                m_Browser_OsdRect.uiWidth   = POS_TV_NTSC_BROWSER_OSD_W;
                m_Browser_OsdRect.uiHeight  = POS_TV_NTSC_BROWSER_OSD_H;

                m_BrowserDraw_Tv[BROWSER_GUI_SD_STATE].m_PosX = POS_TV_NTSC_BRO_MEDIA_X;
                m_BrowserDraw_Tv[BROWSER_GUI_SD_STATE].m_PosY = POS_TV_NTSC_BRO_MEDIA_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_BATTERY].m_PosX = POS_TV_NTSC_BRO_BATT_X;
                m_BrowserDraw_Tv[BROWSER_GUI_BATTERY].m_PosY = POS_TV_NTSC_BRO_BATT_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_FILENAME].m_PosX = POS_TV_NTSC_BRO_NAME_X;
                m_BrowserDraw_Tv[BROWSER_GUI_FILENAME].m_PosY = POS_TV_NTSC_BRO_NAME_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_FILE_DATE].m_PosX = POS_TV_NTSC_BRO_DATE_X;
                m_BrowserDraw_Tv[BROWSER_GUI_FILE_DATE].m_PosY = POS_TV_NTSC_BRO_DATE_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_MOV_TOTAL_TIME].m_PosX = POS_TV_NTSC_BRO_TOTALTIME_X;
                m_BrowserDraw_Tv[BROWSER_GUI_MOV_TOTAL_TIME].m_PosY = POS_TV_NTSC_BRO_TOTALTIME_Y;

                m_BrowserDraw_Parameters_Active = sBrowserDraw_Hdmi_Parameters_NTSC;
            }
            break;

        default:
        case TV_SYSTEM_PAL:
            {
                UI_DARW_BROWSER_PARAMETERS sBrowserDraw_Hdmi_Parameters_PAL = UI_DARW_BROWSER_TV_PAL_PARAMETERS;

                m_Browser_OsdRect.uiLeft        = POS_TV_PAL_BROWSER_OSD_X0;
                m_Browser_OsdRect.uiTop         = POS_TV_PAL_BROWSER_OSD_Y0;
                m_Browser_OsdRect.uiWidth   = POS_TV_PAL_BROWSER_OSD_W;
                m_Browser_OsdRect.uiHeight  = POS_TV_PAL_BROWSER_OSD_H;

                m_BrowserDraw_Tv[BROWSER_GUI_SD_STATE].m_PosX = POS_TV_PAL_BRO_MEDIA_X;
                m_BrowserDraw_Tv[BROWSER_GUI_SD_STATE].m_PosY = POS_TV_PAL_BRO_MEDIA_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_BATTERY].m_PosX = POS_TV_PAL_BRO_BATT_X;
                m_BrowserDraw_Tv[BROWSER_GUI_BATTERY].m_PosY = POS_TV_PAL_BRO_BATT_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_FILENAME].m_PosX = POS_TV_PAL_BRO_NAME_X;
                m_BrowserDraw_Tv[BROWSER_GUI_FILENAME].m_PosY = POS_TV_PAL_BRO_NAME_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_FILE_DATE].m_PosX = POS_TV_PAL_BRO_DATE_X;
                m_BrowserDraw_Tv[BROWSER_GUI_FILE_DATE].m_PosY = POS_TV_PAL_BRO_DATE_Y;

                m_BrowserDraw_Tv[BROWSER_GUI_MOV_TOTAL_TIME].m_PosX = POS_TV_PAL_BRO_TOTALTIME_X;
                m_BrowserDraw_Tv[BROWSER_GUI_MOV_TOTAL_TIME].m_PosY = POS_TV_PAL_BRO_TOTALTIME_Y;

                m_BrowserDraw_Parameters_Active = sBrowserDraw_Hdmi_Parameters_PAL;
            }
            break;
    }

}
#endif

