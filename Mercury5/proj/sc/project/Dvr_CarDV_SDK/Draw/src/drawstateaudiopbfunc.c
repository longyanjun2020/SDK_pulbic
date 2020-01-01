/*===========================================================================
 * Include file 
 *===========================================================================*/ 
 
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_dcf.h"
#include "ahc_browser.h"
#include "ahc_menu.h"
#include "ahc_utility.h"
#include "ahc_display.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
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

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

#if (AUDIO_REC_PLAY_EN)
static UINT32 	m_ulCurAudioPlayTime  = 0;
static UINT32	m_ulCurAudioTotalTime = 0;
extern AHC_OSD_INSTANCE *m_OSD[];
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/ 

extern UINT8 	m_ubBatteryStatus;
extern UINT8 	bAudioState; 
extern AHC_BOOL	bLockCurAudFile;
extern UINT32	m_AudPlayFFSpeed;
extern UINT32	m_AudPlayREWSpeed;

/*===========================================================================
 * Main body 
 *===========================================================================*/ 

void UpdateAudPBStatus(UINT8 ubStatus)
{
	bAudioState = ubStatus;
}

#if (AUDIO_REC_PLAY_EN)

void DrawAudPb_Status(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    GUI_BITMAP 	Icon	= bmIcon_HdmiVideoPlay_Pause;
 
    AHC_OSDSetColor(ubID, bkColor);
    AHC_OSDDrawFillRect(ubID, x, y, x+50, y+35);  
    
    switch(bAudioState)
    {
    	case AUDIO_STATE_PLAY:
    	    Icon = bmIcon_HdmiVideoPlay_Play;
    	    AHC_OSDSetColor(ubID, 0xAA000000);
        	AHC_OSDDrawBitmap(ubID, &Icon, x, y);
    	break;
    
    	case AUDIO_STATE_PAUSE:   	
    		Icon = bmIcon_HdmiVideoPlay_Pause;
    	    AHC_OSDSetColor(ubID, 0xAA000000);
        	AHC_OSDDrawBitmap(ubID, &Icon, x, y);
    	break;
    	
    	case AUDIO_STATE_FF:
    		Icon = bmIcon_HdmiVideoPlay_FF;
        	AHC_OSDSetColor(ubID, 0xAA000000);
        	AHC_OSDDrawBitmap(ubID, &Icon, x, y);
        	AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        	AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
    		AHC_OSDDrawDec(ubID, m_AudPlayFFSpeed, x+Icon.XSize+7, y+2, 1);
    		AHC_OSDDrawText(ubID, (UINT8*)"X", x+Icon.XSize+17, y+2, strlen("X"));
    	break;

    	case AUDIO_STATE_REW:
    		Icon = bmIcon_HdmiVideoPlay_FB;
    	    AHC_OSDSetColor(ubID, 0xAA000000);
        	AHC_OSDDrawBitmap(ubID, &Icon, x, y);
        	AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        	AHC_OSDSetFont(ubID, &GUI_Font16B_ASCII);
    		AHC_OSDDrawDec(ubID, m_AudPlayREWSpeed, x+Icon.XSize+7, y+2, 1);
    		AHC_OSDDrawText(ubID, (UINT8*)"X", x+Icon.XSize+17, y+2, strlen("X"));        	
    	break;

   		default:
   		break; 
    }
}

void DrawAudPb_ProgressBar(UINT8 ubID, UINT32 CurTime, UINT32 MaxTime, AHC_BOOL bClear)
{ 
    UINT16 BarStartX 	= 40;
    UINT16 BarStartY 	= 140;
    UINT32 MaxBarLine 	= m_OSD[ubID]->width - BarStartX*2;
    UINT32 BarPos;
    static UINT32  tempBarPos = 0;

    BarPos = (MaxBarLine * CurTime) / MaxTime;

    if(BarPos == tempBarPos)
        return;

    tempBarPos = BarPos;    
    
	if(bClear)
	{
		AHC_OSDSetColor(ubID, OSD_COLOR_BLACK);
		AHC_OSDDrawFillRect(ubID, BarStartX-5, BarStartY-5, BarStartX+MaxBarLine+5, BarStartY+5);
	}
	else
	{
	    AHC_OSDSetColor(ubID, OSD_COLOR_RED);
	    AHC_OSDSetPenSize(ubID, 3);
	      
	    AHC_OSDDrawLine(ubID, BarStartX, 				BarStartX+BarPos, 		BarStartY+2, BarStartY+2);
	    
	    AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
	    AHC_OSDSetPenSize(ubID, 1);
	    
	    AHC_OSDDrawLine(ubID, BarStartX, 				BarStartX+MaxBarLine, 	BarStartY, 	 BarStartY);
	    AHC_OSDDrawLine(ubID, BarStartX, 				BarStartX+MaxBarLine, 	BarStartY+5, BarStartY+5);
	    AHC_OSDDrawLine(ubID, BarStartX-1, 				BarStartX-1, 			BarStartY-2, BarStartY+5);
	    AHC_OSDDrawLine(ubID, BarStartX+MaxBarLine+1, 	BarStartX+MaxBarLine+1, BarStartY-2, BarStartY+5);
	}
}

void DrawAudPb_FileIndex(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    DrawMovPb_FileIndex(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawAudPb_FileInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    DrawMovPb_FileInfo(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawAudPb_PlayInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
	UINT32 	ulCurPlayTime;
    UINT16  leftpos 	= x;
    UINT8   nDigit 		= 2;
    UINT16 	WordWidth 	= 7;
    UINT8  	CharWidth 	= 5;

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
		   
        AHC_GetAudioCurrentTime(&ulCurPlayTime);
		
		DrawAudPb_ProgressBar(ubID, ulCurPlayTime, m_ulCurAudioTotalTime, AHC_FALSE);

		if(m_ulCurAudioPlayTime != ulCurPlayTime)
        {
            m_ulCurAudioPlayTime = ulCurPlayTime;
        }
        else if(GetAudConfig()->iState == AUD_STATE_PAUSE)
        {
        	//NOP
        }
        else
        	return; 

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDSetPenSize(ubID, 3);
 
        AHC_OSDDrawDec(ubID, TIME_HOUR(m_ulCurAudioPlayTime), leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_MIN(m_ulCurAudioPlayTime),  leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_SEC(m_ulCurAudioPlayTime),  leftpos, y, nDigit);    
    }
}

void DrawAudPb_TotalTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
	AUDIO_ATTR  Info;
    UINT16  	leftpos 	= x;
    UINT8   	nDigit 		= 2;
    UINT16 		WordWidth 	= 7;
    UINT8  		CharWidth 	= 5;

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
    
        AHC_GetAudioFileAttr(&Info);
        
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDSetPenSize(ubID, 3);
		
		m_ulCurAudioTotalTime = Info.total_time;
		
		AHC_OSDDrawText(ubID,(UINT8*)"/", leftpos ,y, strlen("/"));

        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_HOUR(Info.total_time), leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_MIN(Info.total_time),  leftpos, y, nDigit);
        leftpos += nDigit*WordWidth;
        AHC_OSDDrawText(ubID,(UINT8*)":", leftpos ,y, strlen(":"));
        leftpos += CharWidth;
        AHC_OSDDrawDec(ubID, TIME_SEC(Info.total_time),  leftpos, y, nDigit); 
    }	
}

void DrawAudPb_LockCurFile(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (QUICK_FILE_EDIT_EN)
    GUI_BITMAP 	IconID 	= BMICOM_FILE_PROTECTKEY;
   
   	if(bFlag==AHC_FALSE)
   	{
		AHC_OSDSetColor(ubID, bkColor);
    	AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
    	AHC_OSDSetColor(ubID, 0xAA000000);
   	}
   	else
   	{	
   		if(bLockCurAudFile)
   		{
	        if(bLarge==LARGE_SIZE)
	        	AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
	        else
	        	AHC_OSDDrawBitmap(ubID, &IconID, x, y);
		}
	}
#endif
}

void DrawStateAudPbState(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);
    
	UIDrawAudPBFuncEx(bID0, AUDPB_GUI_STATUS, AHC_TRUE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
}

void DrawStateAudPbInit(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
	UINT8  idx 	= 0;

	CHARGE_ICON_ENABLE(AHC_FALSE);

	MMPS_Display_SetWinActive(LOWER_IMAGE_WINDOW_ID, MMP_FALSE);//TBD
    
    OSDDraw_GetLastOvlDrawBuffer(&bID0);
    
    OSDDraw_ClearOvlDrawBuffer(bID0);

    OSDDraw_SetAlphaBlending(bID0, AHC_FALSE);
    OSDDraw_SetAlphaBlending(bID1, AHC_TRUE);

    AHC_OSDSetCurrentDisplay(bID0);
    AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
	AHC_OSDDrawFillRect(bID0, 0, 0, m_OSD[bID0]->width, m_OSD[bID0]->height);
    AHC_OSDSetColor(bID1, OSD_COLOR_BLACK);
	AHC_OSDDrawFillRect(bID1, 0, 0, m_OSD[bID1]->width, m_OSD[bID1]->height);
	
	AHC_OSDDrawBitmap(bID0, &bmIcon_Music, (m_OSD[bID0]->width-76)/2, 60);
		
	for (idx = 0; idx < AUDPB_GUI_MAX; idx++)
	{
		if(idx==AUDPB_GUI_CUR_TIME)
		{
			 if(bAudioState != AUDIO_STATE_PLAY)	
				UIDrawAudPBFuncEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
		}
		else	
			UIDrawAudPBFuncEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
	}

	CHARGE_ICON_ENABLE(AHC_TRUE);
}

void DrawStateAudPbChangeFile(void)
{
    UINT8  bID0 = 0;

    OSDDraw_GetLastOvlDrawBuffer(&bID0);

	UIDrawAudPBFuncEx(bID0, AUDPB_GUI_FILENAME,   AHC_FALSE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
	UIDrawAudPBFuncEx(bID0, AUDPB_GUI_FILE_INDEX, AHC_TRUE,  AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
	UIDrawAudPBFuncEx(bID0, AUDPB_GUI_TOTAL_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif
}

void DrawStateAudPbUpdate(void)
{
    UINT8    bID0 = 0;
    static UINT8 	SD_status = AHC_FALSE;
#if (QUICK_FILE_EDIT_EN)
    static UINT8 	Lock_status = AHC_FALSE;
#endif
    	
    OSDDraw_GetLastOvlDrawBuffer(&bID0);

    if(m_ubBatteryStatus != MenuSettingConfig()->uiBatteryVoltage)
    {
        UIDrawAudPBFuncEx(bID0, AUDPB_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
        m_ubBatteryStatus = MenuSettingConfig()->uiBatteryVoltage;
    }
    
    if(SD_status != AHC_SDMMC_IsSD1MountDCF()) 
    {
        UIDrawAudPBFuncEx(bID0, AUDPB_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);
        //SD_status = AHC_SDMMC_GetMountState();
    }

#if (QUICK_FILE_EDIT_EN) 
    if(Lock_status != bLockCurAudFile)
    {
        UIDrawAudPBFuncEx(bID0, AUDPB_GUI_LOCK_FILE, AHC_TRUE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);	
        Lock_status = bLockCurAudFile;
    }
#endif
    
#if	OSD_SHOW_BATTERY_STATUS == 1
    AHC_DrawChargingIcon_UsingTimer(bID0);
#endif

    UIDrawAudPBFuncEx(bID0, AUDPB_GUI_CUR_TIME, AHC_FALSE, AHC_TRUE, OSD_COLOR_BLACK, NULL_PARAM);

#ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
#endif
}

void DrawStateAudPbMode_Update(void)
{
	DrawStateAudPbInit();    
}

#endif

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStateAudPlaybackUpdate( UINT32 ubEvent)
{
#if (AUDIO_REC_PLAY_EN)

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
			AHC_OSDSetFlipDrawMode(OVL_DISPLAY_BUFFER, OSD_FLIP_DRAW_NONE_ENABLE);
			DrawStateAudPbInit();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
        break;
        
        case EVENT_MOVPB_MODE_INIT                : 
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			DrawStateAudPbInit();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
        break; 
                                                                                                                                 
        case EVENT_MOVPB_NEXT_PRESS         :
        case EVENT_MOVPB_PREV_PRESS         :
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			DrawStateAudPbChangeFile();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
        break;

        case EVENT_MOVPB_PLAY_START:
        case EVENT_MOVPB_PAUSE:
        case EVENT_KEY_LEFT:
        case EVENT_KEY_RIGHT:
        	DrawStateAudPbState();        
        break;
              
        case EVENT_MOVPB_UPDATE_MESSAGE           : 
			DrawStateAudPbUpdate();
        break;
        
        case EVENT_MENU_RETURN:
        	DrawStateAudPbMode_Update();
        break;
        
        default:
        break;
    }
#endif        
}



