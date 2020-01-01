/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_browser.h"
#include "ahc_menu.h"
#include "ahc_utility.h"
#include "ahc_display.h"
#include "ahc_mediaplayback.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuTouchButton.h"
#include "keyparser.h"
#include "MenuSetting.h"
#include "DrawStateMenuSetting.h"
#include "drawstatemoviepbfunc.h"
#include "ColorDefine.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "OSDStrings.h"
#include "dsc_charger.h"
#include "mediaplaybackctrl.h"
#include "ui_drawgeneral.h"
#include "ShowOSDFunc.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

static UINT32 	tCurrentPlayTime 	= 0;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern UINT8 	m_ubBatteryStatus;
extern AHC_BOOL	bLockCurMovFile;
extern UINT32	m_MovPlayFFSpeed;
extern UINT32	m_MovPlayREWSpeed;
extern UINT8 	bMovieState;
//extern UINT8 	bTVMovieState;
extern UINT8 	bHdmiMovieState;
extern UINT32 	m_VideoCurPlayTime;
extern AHC_BOOL	bMovPbEnterToHdmi;
extern AHC_BOOL	bMovPbEnterToTV;
extern AHC_BOOL m_ubPlaybackRearCam;
extern AHC_BOOL gbAhcDbgBrk;
//extern UINT8 						m_DelFile;
/*===========================================================================
 * Main body
 *===========================================================================*/

typedef enum _TV_DELETE_OP
{
	DEL_FILE_NONE = 0,
	DEL_FILE_SELECT_NO,
	DEL_FILE_SELECT_YES,
	DEL_FILE_DECIDE_NO,
	DEL_FILE_DECIDE_YES
} TV_DELETE_OP;


void UpdateMovPBStatus(UINT8 ubStatus)
{
	bMovieState = ubStatus;
}

void DrawMovPb_Status(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    GUI_BITMAP 	IconDir			= bmIcon_HdmiVideoPlayStop;
    GUI_BITMAP 	IconState 		= bmIcon_HdmiVideoPlay_Pause;
    AHC_BOOL	bClearTrashCan 	= AHC_FALSE;
    UINT8		CurState 		= MOVIE_STATE_PLAY;
    UINT32		OffX, OffY;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

 	if(bFlag==AHC_FALSE)
 	{
    	AHC_OSDSetColor(ubID, bkColor);
    	AHC_OSDSetBkColor(ubID, bkColor);

    	if(bLarge==LARGE_SIZE)
    		AHC_OSDDrawFillRect(ubID, x, y, x+80, y+35);
    	else
    		AHC_OSDDrawFillRect(ubID, x, y, x+50, y+35);
    }
    else
    {
	CurState = bMovieState;

    	if(bLarge==LARGE_SIZE)
    	{
    		AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
    		OffX = 25;
    		OffY = 8;
    	}
    	else
    	{
    		AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
    		OffX = 7;
    		OffY = 2;
    	}

	    switch(CurState)
	    {
			case MOVIE_STATE_STOP :
				IconDir   = bmIcon_HdmiVideoPlayStop;
				IconState = bmIcon_HdmiVideoPlay_Stop;
				bClearTrashCan = AHC_TRUE;
			break;

	    	case MOVIE_STATE_PLAY:
				IconDir   = bmIcon_HdmiVideoPlay;
				IconState = bmIcon_HdmiVideoPlay_Play;
				bClearTrashCan = AHC_FALSE;
	    	break;

	    	case MOVIE_STATE_PAUSE:
				IconDir   = bmIcon_HdmiVideoPlayPause;
				IconState = bmIcon_HdmiVideoPlay_Pause;
				bClearTrashCan = AHC_TRUE;
	    	break;

	    	case MOVIE_STATE_FF:
				IconDir   = bmIcon_HdmiVideoPlay;
				IconState = bmIcon_HdmiVideoPlay_FF;
				bClearTrashCan = AHC_FALSE;

	        	AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
	    		AHC_OSDDrawDec(ubID, m_MovPlayFFSpeed, x+IconState.XSize+OffX, y+OffY, 1);
	    		AHC_OSDDrawText(ubID, (UINT8*)"X", x+IconState.XSize+OffX+10, y+OffY, strlen("X"));
	    	break;

	    	case MOVIE_STATE_REW:
				IconDir   = bmIcon_HdmiVideoPlay;
				IconState = bmIcon_HdmiVideoPlay_FB;
				bClearTrashCan = AHC_FALSE;

	        	AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
	    		AHC_OSDDrawDec(ubID, m_MovPlayREWSpeed, x+IconState.XSize+OffX, y+OffY, 1);
	    		AHC_OSDDrawText(ubID, (UINT8*)"X", x+IconState.XSize+OffX+10, y+OffY, strlen("X"));
	    	break;

			case MOVIE_STATE_PFF   :
				IconDir   = bmIcon_HdmiVideoPlayPause;
				IconState = bmIcon_HdmiVideoPlay_PFF;
				bClearTrashCan = AHC_TRUE;
			break;

			case MOVIE_STATE_PFB   :
				IconDir   = bmIcon_HdmiVideoPlayPause;
				IconState = bmIcon_HdmiVideoPlay_PFB;
				bClearTrashCan = AHC_TRUE;
			break;

	   		default:
	   		break;
	    }

	    if(bLarge==LARGE_SIZE)
	    {
			#if 0//(SHOW_TV_DIR_ICON)
			AHC_OSDDrawBitmap(ubID, &IconDir, x+60, y);

			if(bClearTrashCan)
				DrawClearTrashCan(ubID);
			#endif

			AHC_OSDDrawBitmapMag(ubID, &IconState, x, y, ubMag, ubMag);
	    }
	    else
	    {
			AHC_OSDSetColor(ubID, 0xAA000000);
			AHC_OSDDrawBitmap(ubID, &IconState, x, y);
	    }
    }

	END_LAYER(ubID);
}

void DrawMovPb_FileIndex(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32  CurObjIdx 	= 0;
    UINT32  MaxObjIdx 	= 0;
    UINT8   nDigitM	    = 0, nDigitC = 0;
    UINT16  leftpos 	= x;
    UINT16  WordWidth 	= 7;
    UINT16  CharWidth 	= 5;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    AHC_UF_GetTotalFileCount(&MaxObjIdx);
    AHC_UF_GetCurrentIndex(&CurObjIdx);
    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    nDigitM = NumOfDigit(MaxObjIdx);
    nDigitC = NumOfDigit(CurObjIdx+1);

    BEGIN_LAYER(ubID);

    if(bLarge==LARGE_SIZE)
    {
        AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
        WordWidth = 14;
        CharWidth = 9;
    }
    else
    {
        AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
        WordWidth = 7;
        CharWidth = 5;
	}

	if(bFlag==AHC_FALSE)
	{
        AHC_OSDSetColor(ubID, bkColor);
		AHC_OSDDrawFillRect(ubID, x, y, x+WordWidth*(nDigitM+nDigitC+2), y+WordWidth+8);
    }
    else
    {
	    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDSetPenSize(ubID, 3);

		leftpos = x;
        AHC_OSDDrawDec(ubID, CurObjIdx+1, leftpos, y, nDigitC);

        leftpos += nDigitC*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos , y, strlen("/"));

        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, MaxObjIdx,   leftpos, y, nDigitM);
    }

	END_LAYER(ubID);
}

void DrawMovPb_FileInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32   	CurObjIdx;
    INT8         FileName[MAX_FULL_FILENAME_SIZE];

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag==AHC_TRUE)
    {
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }
		AHC_UF_GetCurrentIndex(&CurObjIdx);
        AHC_UF_GetFileNamebyIndex(CurObjIdx,FileName);
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
        	AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
        else {
        	AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
       	}

        AHC_OSDDrawText(ubID, (UINT8*)FileName, x, y, strlen(FileName));
    }

	END_LAYER(ubID);
}

void DrawMovPb_DateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32      CurObjIdx;
    UINT16      leftpos 	= x;
    UINT16      WordWidth	= 7;
    UINT16      CharWidth	= 5;
    AHC_RTC_TIME RtcTime;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

  	if(bFlag==AHC_TRUE)
  	{
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }
	    AHC_UF_GetCurrentIndex(&CurObjIdx);
        AHC_UF_GetFileTimebyIndex(CurObjIdx, &RtcTime);
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }

	    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
	    AHC_OSDSetBkColor(ubID, bkColor);
	    AHC_OSDSetPenSize(ubID, 3);

	    if(bLarge==LARGE_SIZE)
	    {
	        AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
	        WordWidth = 14;
	        CharWidth = 9;
	    }
	    else
	    {
	        AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
	        WordWidth = 7;
	        CharWidth = 5;
		}

	    AHC_OSDDrawDec(ubID, RtcTime.uwYear, leftpos, y, 4);

	    leftpos += WordWidth*4;
	    AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos, y, strlen("/"));

	    leftpos += CharWidth;
	    AHC_OSDDrawDec(ubID, RtcTime.uwMonth, leftpos, y, 2);

	    leftpos += WordWidth*2;
	    AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos, y, strlen("/"));

	    leftpos += CharWidth;
	    AHC_OSDDrawDec(ubID, RtcTime.uwDay, leftpos, y, 2);

	    leftpos += WordWidth*2;
	    AHC_OSDDrawText(ubID,(UINT8*)" ", leftpos, y, strlen(" "));

	    leftpos += CharWidth;
	    AHC_OSDDrawDec(ubID, RtcTime.uwHour, leftpos, y, 2);

	    leftpos += WordWidth*2;
	    AHC_OSDDrawText(ubID,(UINT8*)":", leftpos, y, strlen(":"));

	    leftpos += CharWidth;
	    AHC_OSDDrawDec(ubID, RtcTime.uwMinute, leftpos, y, 2);
    }

	END_LAYER(ubID);
}

void DrawMovPb_PlayInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32 	ulCurPlayTime;
    UINT16  leftpos 	= x;
    UINT8   nDigit 		= 2;
    UINT16 	WordWidth 	= 7;
    UINT8  	CharWidth 	= 5;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag==AHC_TRUE)
    {
		if(bLarge==LARGE_SIZE)
		{
			WordWidth = 14;
			CharWidth = 9;
			AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
		}
		else
		{
			WordWidth = 7;
			CharWidth = 5;
			AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
		}

        AHC_GetVideoCurrentPlayTime(&ulCurPlayTime);

		if(tCurrentPlayTime != ulCurPlayTime)
        {
            tCurrentPlayTime = ulCurPlayTime;
        }
        else if(GetMovConfig()->iState == MOV_STATE_PAUSE)
        {
        	if(bMovPbEnterToHdmi || bMovPbEnterToTV)
        		tCurrentPlayTime = m_VideoCurPlayTime;
        }
        else {
			END_LAYER(ubID);
			return;
		}

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDSetPenSize(ubID, 3);

        AHC_OSDDrawDec(ubID, TIME_HOUR(tCurrentPlayTime), leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_MIN(tCurrentPlayTime),  leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_SEC(tCurrentPlayTime),  leftpos, y, nDigit);
    }

	END_LAYER(ubID);
}

void DrawMovPb_TotalTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    AHC_VIDEO_ATTR  Info;
    UINT16  leftpos 	= x;
    UINT8   nDigit 		= 2;
    UINT16 	WordWidth 	= 7;
    UINT8  	CharWidth 	= 5;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag==AHC_TRUE)
    {
		if(bLarge==LARGE_SIZE)
		{
			WordWidth = 14;
			CharWidth = 9;
			AHC_OSDSetFont(ubID, &GUI_Font24B_ASCII);
		}
		else
		{
			WordWidth = 7;
			CharWidth = 5;
			AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
		}

        AHC_GetVideoFileAttr(&Info);

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDSetPenSize(ubID, 3);

		AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_HOUR(Info.TotalTime), leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_MIN(Info.TotalTime),  leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_SEC(Info.TotalTime),  leftpos, y, nDigit);
    }

	END_LAYER(ubID);
}

void DrawMovPB_VolumeBar(AHC_BOOL bClear)
{
    #define OffsetH (26)

    static UINT16 uwVolIdx = 0;
    UINT8 		i;
    RECT 		rc = {89 , 160+OffsetH , 10, 12};
    UINT16 		Left_temp;
    GUI_COLOR 	FillColor;
    UINT8 		ubID = MAIN_DISPLAY_BUFFER;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);
    AHC_OSDSetActive(ubID, 1);

    if(bClear)
    {
        AHC_OSDSetColor(ubID, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(ubID, 65, 155+OffsetH, 245, 190+OffsetH);
        AHC_OSDSetActive(ubID, 0);
		END_LAYER(ubID);

        return;
    }

    uwVolIdx = MenuSettingConfig()->uiVolume;

    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(ubID, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetFont(ubID, &GUI_Font16B_1);

    AHC_OSDDrawText(ubID, (UINT8*)"_", 76,  150+OffsetH, 1);
    AHC_OSDDrawText(ubID, (UINT8*)"+", 232, 156+OffsetH, 1);

    for(i=0; i<10; i++)
    {
        Left_temp = rc.uiLeft + ( rc.uiWidth + 4 ) * i;

        if(i < uwVolIdx)
            FillColor = OSD_COLOR_GREEN;
        else
            FillColor = 0xFF111111;

        AHC_OSDSetColor(ubID, OSD_COLOR_BLACK);
        AHC_OSDDrawRect(ubID, Left_temp, rc.uiTop, Left_temp+rc.uiWidth, rc.uiTop+rc.uiHeight);

        AHC_OSDSetColor(ubID, FillColor);
        AHC_OSDDrawFillRect(ubID, Left_temp+1, rc.uiTop+1, Left_temp+rc.uiWidth-1, rc.uiTop+rc.uiHeight-1);
    }

	END_LAYER(ubID);
}

void DrawHdmiMoviePB_VolumeBar(UINT8 ubID, AHC_BOOL bForce)
{

}
void DrawMovPb_LockCurFile(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (QUICK_FILE_EDIT_EN)
    GUI_BITMAP 	IconID 	= BMICOM_FILE_PROTECTKEY;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

   	if(bFlag==AHC_FALSE)
   	{
		AHC_OSDSetColor(ubID, bkColor);
    	AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
    	AHC_OSDSetColor(ubID, 0xAA000000);
   	}
   	else
   	{
   		if(bLockCurMovFile)
   		{
	        if(bLarge==LARGE_SIZE)
	        	AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
	        else
	        	AHC_OSDDrawBitmap(ubID, &IconID, x, y);
		}
	}

	END_LAYER(ubID);
#endif
}

void DrawStateMovPbState(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, MOVPB_GUI_STATUS, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}

void DrawStateMovPbStateWithTouchButton(void)
{
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI

    UINT8  bID0 = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, MOVPB_GUI_STATUS, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect(bID0, 90, 50, AHC_GET_ATTR_OSD_W(bID0), 190);

    OSDDraw_CtrlTouchButton(bID0, UI_PLAYBACK_STATE);

#ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
#endif

    END_LAYER(bID0);

#endif
}

void DrawStateMovPbPageSwitch(UINT8 ubPage)
{
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
    UINT8  bID0 = 0;

	OSDDraw_GetLastOvlDrawBuffer(&bID0);

    OSDDraw_ClearTouchButtons(bID0, MovPBCtrlPage_TouchButton, ITEMNUM(MovPBCtrlPage_TouchButton));

    BEGIN_LAYER(bID0);
    if( TOUCH_MAIN_PAGE == ubPage )
        OSDDraw_MainTouchButton(bID0, UI_PLAYBACK_STATE);
	else
        OSDDraw_CtrlTouchButton(bID0, UI_PLAYBACK_STATE);
    END_LAYER(bID0);
#endif
}

void DrawStateMovPbInit(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    UINT8  idx 	= 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    CHARGE_ICON_ENABLE(AHC_FALSE);

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

#ifdef FLM_GPIO_NUM
    AHC_OSDSetActive(bID0, AHC_FALSE);
#endif

    OSDDraw_ClearOvlDrawBuffer(bID0);

    BEGIN_LAYER(bID0);

    //OSDDraw_EnableSemiTransparent( 1, 	AHC_TRUE );
    OSDDraw_EnableSemiTransparent( bID0, AHC_TRUE );
    //OSDDraw_EnableSemiTransparent( bID1, AHC_TRUE );

    AHC_OSDSetCurrentDisplay(bID0);

    AHC_OSDSetColor(bID0, 0xFF000000);

    END_LAYER(bID0);

    for (idx = 0; idx < MOVPB_GUI_MAX; idx++)
    {
        if(idx==MOVPB_GUI_CUR_TIME)
        {
            if(bMovieState != MOVIE_STATE_PLAY)
                UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        }
        else
            UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    BEGIN_LAYER(bID0);
    OSDDraw_MainTouchButton(bID0, UI_PLAYBACK_STATE);
    END_LAYER(bID0);
	AHC_OSDSetActive(bID0, AHC_TRUE);

#ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
#endif
	AHC_OSDRefresh();

    CHARGE_ICON_ENABLE(AHC_TRUE);
}
void DrawStateHdmiMoviePBInit(UINT8 bID0, UINT8 bID1)
{
    UINT8   idx;
    UINT32 	iVal[2];
    RECT  	OsdRect  = POS_HDMI_PLAY_OSD;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);
    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(bID0, &OsdRect);
    END_LAYER(bID0);

    for (idx = 0; idx < MOVPB_GUI_MAX; idx++)
    {
        if(idx==MOVPB_GUI_CUR_TIME)
        {
            if(bMovieState != MOVIE_STATE_PLAY)
                UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        }
        else
            UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

#if (POWER_OFF_CONFIRM_PAGE_EN)
    if(PowerOff_InProcess)
    {
        MenuDrawSubPage_PowerOff_HDMI_Play(bID0);
    }
#endif

    iVal[0] = 1;
    iVal[1] = OSD_COLOR_TRANSPARENT;
    AHC_OSDSetDisplayAttr(bID0, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);
    AHC_OSDSetDisplayAttr(bID1, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

void DrawStateMovPbChangeFile(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

	UIDrawEx(bID0, MOVPB_GUI_FILENAME,   AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
	UIDrawEx(bID0, MOVPB_GUI_FILE_INDEX, AHC_TRUE,  AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_TOTAL_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif
}

void DrawStateMovPbUpdate(void)
{
    UINT8    bID0 = 0;
	static UINT8 	SD_status = AHC_FALSE;
#if (QUICK_FILE_EDIT_EN)
    static UINT8 	Lock_status = AHC_FALSE;
#endif

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    if(m_ubBatteryStatus != MenuSettingConfig()->uiBatteryVoltage)
	{
   		UIDrawEx(bID0, MOVPB_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    	m_ubBatteryStatus = MenuSettingConfig()->uiBatteryVoltage;
    }

    if(SD_status != AHC_SDMMC_IsSD1MountDCF())
    {
    	UIDrawEx(bID0, MOVPB_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        //SD_status = AHC_SDMMC_GetMountState();
    }

#if (QUICK_FILE_EDIT_EN)
 	if(Lock_status != bLockCurMovFile)
	{
		UIDrawEx(bID0, MOVPB_GUI_LOCK_FILE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
		Lock_status = bLockCurMovFile;
	}
#endif

#if	OSD_SHOW_BATTERY_STATUS == 1
	AHC_DrawChargingIcon_UsingTimer(bID0);
#endif

    UIDrawEx(bID0, MOVPB_GUI_CUR_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif
}

void DrawStateMovPbMode_Update(void)
{
	DrawStateMovPbInit();
}



void DrawStateHdmiMoviePBPlayInfo(void)
{
    UINT8    bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, MOVPB_GUI_CUR_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}

void DrawStateHdmiMoviePBDel(UINT8 state)
{
    UINT8  	bID0 		= 0;
    RECT  	OsdRect  	= POS_HDMI_PLAY_OSD;
    RECT 	StrDelRECT 	= {30,  70,  200, 20};
    RECT 	StrYesRECT 	= {15,  100, 102, 36};
    RECT 	StrNoRECT 	= {140, 100, 102, 36};
    RECT 	tmpRECT;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    BEGIN_LAYER(bID0);
    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect(bID0, OsdRect.uiLeft, OsdRect.uiTop+40, OsdRect.uiLeft+OsdRect.uiWidth, OsdRect.uiTop+40+135);

    if(state == DEL_FILE_NONE) {
        END_LAYER(bID0);
        return;
    }

    switch(state) {
	    #if 0
	    case DEL_FILE_NONE: //Clear Buf
	        AHC_OSDSetColor(ubID, OSD_COLOR_TRANSPARENT);
	        AHC_OSDDrawFillRect(bID0, OsdRect.uiLeft, OsdRect.uiTop+40, OsdRect.uiLeft+OsdRect.uiWidth, OsdRect.uiTop+40+135);
	    break;
	    #endif

	    case DEL_FILE_SELECT_NO:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;

	    case DEL_FILE_SELECT_YES:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;

	    case DEL_FILE_DECIDE_NO:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_SELECT, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;

	    case DEL_FILE_DECIDE_YES:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_SELECT, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;
    }

	END_LAYER(bID0);
}

void DrawStateHdmiMoviePBStatus(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, MOVPB_GUI_STATUS, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}

void DrawStateHdmiMoviePBChangeFile(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer( &bID0 );

    UpdateMovPBStatus(MOVIE_STATE_PLAY);

    UIDrawEx(bID0, MOVPB_GUI_FILENAME, 	AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_TOTAL_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_FILE_INDEX, AHC_TRUE,  AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_STATUS, 	AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}

#if (TVOUT_ENABLE)
void DrawStateTVMoviePBInit(UINT8 bID0, UINT8 bID1)
{

    UINT8   idx;
    UINT32 	iVal[2];
    RECT  	OsdRect = POS_TV_PLAY_OSD;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    //OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);

    AHC_OSDDrawFillRect2(bID0, &OsdRect);
    END_LAYER(bID0);

	for (idx = 0; idx < MOVPB_GUI_MAX; idx++)
	{
		if(idx==MOVPB_GUI_CUR_TIME)
		{
                //Andy Liu TBD.
                printc(FG_RED("\r\nPlease modify here!\r\n"));
                AHC_PRINT_RET_ERROR(0, 0);
			 //if(bTVMovieState != MOVIE_STATE_PLAY)
				 UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
		}
		else
			UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
	}

#if (POWER_OFF_CONFIRM_PAGE_EN)
	if(PowerOff_InProcess)
	{
		MenuDrawSubPage_PowerOff_TV_Play(bID0);
	}
#endif

    BEGIN_LAYER(bID0);
    iVal[0] = 1;
    iVal[1] = OSD_COLOR_TRANSPARENT;
    AHC_OSDSetDisplayAttr(bID0, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);
    AHC_OSDSetDisplayAttr(bID1, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);

    //OSDDraw_ExitDrawing(&bID0, &bID1);
    END_LAYER(bID0);
}

void DrawStateTVMoviePBPlayInfo(void)
{
    UINT8    bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, MOVPB_GUI_CUR_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}

void DrawStateTVMoviePBDel(UINT8 state)
{
    UINT8  	bID0 		= 0;
    RECT  	OsdRect  	= POS_TV_PLAY_OSD;
    RECT 	StrDelRECT 	= {30,  70,  200, 20};
    RECT 	StrYesRECT 	= {15,  100, 102, 36};
    RECT 	StrNoRECT 	= {140, 100, 102, 36};
    RECT 	tmpRECT;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect(bID0, OsdRect.uiLeft, OsdRect.uiTop+40, OsdRect.uiLeft+OsdRect.uiWidth, OsdRect.uiTop+40+135);

    if(state == DEL_FILE_NONE) {
        END_LAYER(bID0);

        return;
    }

    switch(state) {
	    #if 0
	    case DEL_FILE_NONE: //Clear Buf
	        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
	        AHC_OSDDrawFillRect(bID0, OsdRect.uiLeft, OsdRect.uiTop+40, OsdRect.uiLeft+OsdRect.uiWidth, OsdRect.uiTop+40+135);
	    break;
	    #endif

	    case DEL_FILE_SELECT_NO:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;

	    case DEL_FILE_SELECT_YES:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;

	    case DEL_FILE_DECIDE_NO:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_SELECT, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;

	    case DEL_FILE_DECIDE_YES:
	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_YELLOW, StrYesRECT.uiLeft, StrYesRECT.uiTop);
	        tmpRECT.uiLeft = StrYesRECT.uiLeft+2; tmpRECT.uiTop = StrYesRECT.uiTop+4; tmpRECT.uiWidth = StrYesRECT.uiWidth-5; tmpRECT.uiHeight = StrYesRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_YES, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_SELECT, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        AHC_OSDDrawBitmap(bID0, &BMICON_SUBBAR_WHITE, StrNoRECT.uiLeft, StrNoRECT.uiTop);
	        tmpRECT.uiLeft = StrNoRECT.uiLeft+2; tmpRECT.uiTop = StrNoRECT.uiTop+4; tmpRECT.uiWidth = StrNoRECT.uiWidth-5; tmpRECT.uiHeight = StrNoRECT.uiHeight-9;
	        OSD_ShowStringPool(bID0,IDS_DS_NO, tmpRECT, OSD_COLOR_FONT, OSD_COLOR_TV_BACKGROUND, GUI_TA_HCENTER|GUI_TA_VCENTER);

	        OSD_ShowStringPool(bID0, IDS_DS_DELETE, StrDelRECT, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_CENTER|GUI_TA_VCENTER);

	        AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
        	AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        	AHC_OSDSetFont(bID0, &GUI_Font16B_ASCII);
        	AHC_OSDDrawText(bID0, (UINT8*)"?", 150, 72, 1);
	    break;
    }

    END_LAYER(bID0);
}

void DrawStateTVMoviePBStatus(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, MOVPB_GUI_STATUS, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}

void DrawStateTVMoviePBChangeFile(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    //UpdateTVMovPBStatus(MOVIE_STATE_PLAY);

    UIDrawEx(bID0, MOVPB_GUI_FILENAME, 	AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_TOTAL_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_FILE_INDEX, AHC_TRUE,  AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, MOVPB_GUI_STATUS, 	AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
}
//void DrawStateHdmiMoviePBUpdate(UINT32 ulEvent)
//{
//#if (HDMI_ENABLE)
//
//    UINT32 uState;
//    UINT8  bID0 = 0;
//    UINT8  bID1 = 0;
//
//    OSDDraw_EnterDrawing(&bID0, &bID1);
//
//    switch( ulEvent )
//    {
//        case EVENT_NONE                           :
//        break;
//
//		case EVENT_KEY_UP                       :
//            AHC_GetSystemStatus(&uState);
//
//            switch(uState)
//            {
//	            case STATE_MOV_IDLE :
//	            break;
//
//	            case STATE_MOV_EXECUTE :
//	            	UpdateMovPBStatus(MOVIE_STATE_REW);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            case STATE_MOV_PAUSE   :
//	            	UpdateMovPBStatus(MOVIE_STATE_PFB);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            default                :
//	            break;
//			}
//        break;
//
//        case EVENT_KEY_DOWN                       :
//            //DrawStateHdmiMoviePBDel(m_DelFile);
//            AHC_GetSystemStatus(&uState);
//
//            switch(uState)
//            {
//	            case STATE_MOV_IDLE :
//	            break;
//
//	            case STATE_MOV_EXECUTE :
//	            	UpdateMovPBStatus(MOVIE_STATE_FF);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            case STATE_MOV_PAUSE   :
//	            	UpdateMovPBStatus(MOVIE_STATE_PFF);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            default                :
//	            break;
//            }
//        break;
//
//        case EVENT_KEY_LEFT                       :
//            AHC_GetSystemStatus(&uState);
//
//            switch(uState)
//            {
//	            case STATE_MOV_IDLE :
//	            break;
//
//	            case STATE_MOV_EXECUTE :
//	            	UpdateMovPBStatus(MOVIE_STATE_REW);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            case STATE_MOV_PAUSE   :
//	            	UpdateMovPBStatus(MOVIE_STATE_PFB);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            default                :
//	            break;
//			}
//        break;
//
//        case EVENT_KEY_RIGHT                      :
//        case EVENT_KEY_CIRCLE                     :
//            AHC_GetSystemStatus(&uState);
//
//            switch(uState)
//            {
//	            case STATE_MOV_IDLE :
//	            break;
//
//	            case STATE_MOV_EXECUTE :
//	            	UpdateMovPBStatus(MOVIE_STATE_FF);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            case STATE_MOV_PAUSE   :
//	            	UpdateMovPBStatus(MOVIE_STATE_PFF);
//					DrawStateHdmiMoviePBStatus();
//	            break;
//
//	            default                :
//	            break;
//            }
//        break;
//
//        case EVENT_HDMI_DEL_FILE                  :
//            DrawStateHdmiMoviePBChangeFile();
//        break;
//
//        case EVENT_HDMI_BROWSER_KEY_PLAYBACK      :
//            if(m_DelFile) {
//                DrawStateHdmiMoviePBDel(m_DelFile+2);
//                break;
//            }
//        break;
//
//        case EVENT_MOVPB_TOUCH_PLAY_PRESS         :
//        	UpdateMovPBStatus(MOVIE_STATE_PLAY);
//			DrawStateHdmiMoviePBStatus();
//        break;
//
//        case EVENT_MOVPB_PAUSE/*EVENT_MOVPB_TOUCH_PAUSE_PRESS*/        :
//
//			AHC_GetVideoPlayStopStatus(&uState);
//
//			if ((AHC_VIDEO_PLAY_EOF == uState) || (AHC_VIDEO_PLAY_ERROR_STOP == uState))
//				UpdateMovPBStatus(MOVIE_STATE_STOP);
//			else
//				UpdateMovPBStatus(MOVIE_STATE_PAUSE);
//
//			DrawStateHdmiMoviePBStatus();
//        break;
//
//        case EVENT_HDMI_PLAY_STOP                 :
//        	UpdateMovPBStatus(MOVIE_STATE_STOP);
//			DrawStateHdmiMoviePBStatus();
//        break;
//
//        case EVENT_MOVPB_UPDATE_MESSAGE           :
//			DrawStateHdmiMoviePBPlayInfo();
//        break;
//
//        case EVENT_HDMI_CHANGE_MODE_INIT          :
//			AHC_OSDSetActive(bID0, 0);
//			AHC_OSDSetActive(bID1, 0);
//			DrawStateHdmiMoviePBInit(bID0, bID1);
//			AHC_OSDSetActive(bID0, 1);
//			AHC_OSDSetActive(bID1, 1);
//        break;
//
//        default:
//        break;
//    }
//
//    OSDDraw_ExitDrawing(&bID0, &bID1);
//
//#endif
//}
void DrawStateTVMoviePBUpdate(UINT32 ulEvent)
{
#if (TVOUT_ENABLE)

    UINT32 uState;
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    switch( ulEvent )
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_DOWN                       :
#if 0  //Andy Liu TBD
            DrawStateTVMoviePBDel(m_DelFile);
#endif
        break;

        case EVENT_KEY_LEFT                       :
            AHC_GetSystemStatus(&uState);

            switch(uState)
            {
	            case STATE_MOV_IDLE :
	            break;

	            case STATE_MOV_EXECUTE :
	            	//UpdateTVMovPBStatus(MOVIE_STATE_REW);
	                DrawStateTVMoviePBStatus();
	            break;

	            case STATE_MOV_PAUSE   :
	            	//UpdateTVMovPBStatus(MOVIE_STATE_PFB);
	                DrawStateTVMoviePBStatus();
	            break;

	            default                :
	            break;
            }
        break;

        case EVENT_KEY_RIGHT                      :
            AHC_GetSystemStatus(&uState);

            switch(uState)
            {
	            case STATE_MOV_IDLE :
	            break;

	            case STATE_MOV_EXECUTE :
	            	//UpdateTVMovPBStatus(MOVIE_STATE_FF);
	                DrawStateTVMoviePBStatus();
	            break;

	            case STATE_MOV_PAUSE   :
	            	//UpdateTVMovPBStatus(MOVIE_STATE_PFF);
	                DrawStateTVMoviePBStatus();
	            break;

	            default                :
	            break;
            }
        break;

        case EVENT_TV_DEL_FILE                  :
            DrawStateTVMoviePBChangeFile();
        break;

        case EVENT_TV_BROWSER_KEY_PLAYBACK      :
#if 0  //Andy Liu TBD
            if(m_DelFile) {
                DrawStateTVMoviePBDel(m_DelFile+2);
                break;
            }
#endif
        break;

        case EVENT_MOVPB_PLAY_START: //EVENT_MOVPB_TOUCH_PLAY_PRESS         :
        	//UpdateTVMovPBStatus(MOVIE_STATE_PLAY);
			DrawStateTVMoviePBStatus();
        break;

        case EVENT_MOVPB_PAUSE/*EVENT_MOVPB_TOUCH_PAUSE_PRESS*/        :

			AHC_GetVideoPlayStopStatus(&uState);
#if 0
			if ((AHC_VIDEO_PLAY_EOF == uState) || (AHC_VIDEO_PLAY_ERROR_STOP == uState))
				UpdateTVMovPBStatus(MOVIE_STATE_STOP);
			else
                UpdateTVMovPBStatus(MOVIE_STATE_PAUSE);
#endif
			DrawStateTVMoviePBStatus();
        break;

        case EVENT_TV_PLAY_STOP                 :
			//UpdateTVMovPBStatus(MOVIE_STATE_STOP);
			DrawStateTVMoviePBStatus();
        break;

        case EVENT_MOVPB_UPDATE_MESSAGE           :
			DrawStateTVMoviePBPlayInfo();
        break;

        case EVENT_TV_CHANGE_MODE_INIT          :
			AHC_OSDSetActive(bID0, 0);
			AHC_OSDSetActive(bID1,0);
			DrawStateTVMoviePBInit(bID0, bID1);
			AHC_OSDSetActive(bID0, 1);
			AHC_OSDSetActive(bID1,1);
        break;

        default:
        break;
    }
    OSDDraw_ExitDrawing(&bID0, &bID1);

#endif
}
#endif //#if (TVOUT_ENABLE)

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStateMovPlaybackUpdate(UINT32 ubEvent)
{
    switch(ubEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_TELE_PRESS                 :
        case EVENT_KEY_WIDE_PRESS                 :
            DrawMovPB_VolumeBar(AHC_FALSE);
        break;

        case EVENT_KEY_WIDE_STOP                  :
        case EVENT_KEY_TELE_STOP                  :
        	DrawMovPB_VolumeBar(AHC_TRUE);
        break;

        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			DrawStateMovPbInit();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
        break;

        case EVENT_MOVPB_MODE_INIT                :
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			DrawStateMovPbInit();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
        break;

        case EVENT_MOVPB_PREV_PRESS         :
        case EVENT_MOVPB_NEXT_PRESS         :
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			DrawStateMovPbChangeFile();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
        break;


        case EVENT_MOVPB_PLAY_START:
        case EVENT_MOVPB_PAUSE:
        case EVENT_KEY_LEFT:
        case EVENT_KEY_RIGHT:
        #if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
        	DrawStateMovPbStateWithTouchButton();
        #else
        	DrawStateMovPbState();
        #endif
        break;

        case EVENT_MOVPB_UPDATE_MESSAGE           :
			DrawStateMovPbUpdate();
        break;

        default:
        break;
    }
}
