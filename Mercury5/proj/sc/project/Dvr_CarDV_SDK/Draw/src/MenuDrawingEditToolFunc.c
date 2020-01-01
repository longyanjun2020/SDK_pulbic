/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_macro.h"
#include "ahc_display.h"
#include "ahc_utility.h"
#include "MenuCommon.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "MenuTouchButton.h"
#include "IconDefine.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "keyparser.h"
#include "ShowOSDFunc.h"
#include "mmps_display.h"
#include "DrawStateMenuSetting.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 


/*===========================================================================
 * Extern varible
 *===========================================================================*/ 

extern PSMENUITEM   sMenuListDeleteOne[];
extern AHC_BOOL 	Deleting_InBrowser;
extern AHC_BOOL 	Delete_Option;
extern AHC_BOOL		Delete_File_Confirm;
extern AHC_BOOL 	Protecting_InBrowser;
extern AHC_BOOL 	Protect_Option;
extern AHC_BOOL		Protect_File_Confirm;
extern AHC_BOOL 	UnProtect_Option;
extern AHC_BOOL		UnProtect_File_Confirm;

/*===========================================================================
 * Extern function
 *===========================================================================*/ 

extern AHC_BOOL AHC_Charger_GetStatus(void);

/*===========================================================================
 * Main body
 *===========================================================================*/ 

#if 0
void ________EditOneFile_Function_________(){ruturn;} //dummy
#endif

void GetConfirmItemRect(int i, RECT* pRc)
{
    AHC_DISPLAY_OUTPUTPANEL OutputDevice;
    AHC_GetDisplayOutputDev(&OutputDevice);
	switch(i)
	{
	    case 1:
        {
            if(OutputDevice == MMP_DISPLAY_SEL_MAIN_LCD){
                static RECT rc = RECT_MENU_CONFIRM_NO;
                *pRc = rc;
            }
            else{
                static RECT rc = RECT_MENU_TV_HDMI_CONFIRM_NO;
                *pRc = rc;
            }
            break;
        }
        case 0:
	    default:
        {
            if(OutputDevice == MMP_DISPLAY_SEL_MAIN_LCD){
                static RECT rc = RECT_MENU_CONFIRM_YES;
                *pRc = rc;
            }
            else{
                static RECT rc = RECT_MENU_TV_HDMI_CONFIRM_YES;
                *pRc = rc;
            }
            break;
        }
	}
}

void DrawSubItem_EditOneFile(UINT16 uwDispID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, GUI_BITMAP* pBar, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect)
{
    RECT rc, tmpRECT;

   	GetConfirmItemRect(iItem%CONFIRM_MENU_PAGE_ITEM, &rc);

    OSD_Draw_IconXY(uwDispID, *pBar, rc.uiLeft, rc.uiTop);

    tmpRECT.uiLeft   = rc.uiLeft 	+ STR_RECT_OFFSET_X; 
    tmpRECT.uiTop    = rc.uiTop 	+ STR_RECT_OFFSET_Y; 
    tmpRECT.uiWidth  = rc.uiWidth 	+ STR_RECT_OFFSET_W; 
    tmpRECT.uiHeight = rc.uiHeight 	+ STR_RECT_OFFSET_H;

    OSD_ShowStringPool3(uwDispID, iStrID, tmpRECT, colorFont, ColorBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
}

/*
 * draw menu page to confirm delete/protect/release file (YES/NO)
 */
void MenuDrawSubPage_EditOneFile(PSMENUSTRUCT pMenu)
{	
	UINT8  		uwDispID = MAIN_DISPLAY_BUFFER;
    UINT32 		i;
	GUI_RECT 	Rect;	
    AHC_DISPLAY_OUTPUTPANEL OutputDevice;
	INT32		iVal[2];

	UINT32 		IconX 	 = RECT_MENU_CONFIRM_ICON_WMSG_X;
	UINT32 		IconY	 = RECT_MENU_CONFIRM_ICON_WMSG_Y;
	UINT32      EditFileWindowWidth  = RECT_MENU_EDITFILE_WINDOW_WIDTH;
	UINT32      EditFileWindowHeight = RECT_MENU_EDITFILE_WINDOW_HEIGHT;  
    RECT        rc = RECT_MENU_CONFIRM_TEXT;
    AHC_GetDisplayOutputDev(&OutputDevice);
    
    if(OutputDevice != MMP_DISPLAY_SEL_MAIN_LCD) 
    {
        UINT16 	Width, Height;
    
    	switch(OutputDevice) 
    	{
	        case MMP_DISPLAY_SEL_HDMI:
	            AHC_GetHdmiDisplayWidthHeight(&Width, &Height);
	        break;    
	        case MMP_DISPLAY_SEL_NTSC_TV:
	            AHC_GetNtscTvDisplayWidthHeight(&Width, &Height);
	        break;    
	        case MMP_DISPLAY_SEL_PAL_TV:
	            AHC_GetPalTvDisplayWidthHeight(&Width, &Height);
	        break;   
        }

		iVal[0] = (Width - EditFileWindowWidth * 2)/2;
		iVal[1] = (Height - EditFileWindowHeight * 2)/2;
        if((iVal[0] < 0) || (iVal[0] > Width) || (iVal[1] < 0) || (iVal[1] > Height)){
            printc("Display Offset out of range!!!\r\n");
        }
		AHC_OSDSetDisplayAttr(uwDispID, AHC_OSD_ATTR_DISPLAY_OFFSET, (UINT32 *)iVal);

		iVal[0] = 1;
		iVal[1] = OSD_COLOR_TRANSPARENT;
		AHC_OSDSetDisplayAttr(uwDispID, AHC_OSD_ATTR_TRANSPARENT_ENABLE, (UINT32 *)iVal);

        iVal[0] = MMP_DISPLAY_DUPLICATE_2X;	// Scale up x2 for Message Box in TV/HDMI
        iVal[1] = MMP_DISPLAY_DUPLICATE_2X;
    }
	else
	{
	    IconX 	 = STRETCH_W(IconX);
	    IconY	 = STRETCH_H(IconY);
	    EditFileWindowWidth  = STRETCH_W(EditFileWindowWidth);
	    EditFileWindowHeight = STRETCH_H(EditFileWindowHeight); 
		#if (SUPPORT_TOUCH_PANEL)
        KeyParser_ResetTouchVariable();
        KeyParser_TouchItemRegister(&Browser_FileEditTouchButton[0], ITEMNUM(Browser_FileEditTouchButton));  
		#endif  	

        if (OSD_DISPLAY_SCALE_LCD) {
            iVal[0] = OSD_DISPLAY_SCALE_LCD - 1;
            iVal[1] = OSD_DISPLAY_SCALE_LCD - 1;
        }
        else {
            iVal[0] = MMP_DISPLAY_DUPLICATE_1X;	// No Scale  for Message Box in LCD
            iVal[1] = MMP_DISPLAY_DUPLICATE_1X;
        }
	}

	AHC_OSDSetDisplayAttr(uwDispID, AHC_OSD_ATTR_DISPLAY_SCALE, (UINT32 *)iVal);
 				
	AHC_OSDSetActive(uwDispID, 0);
	
	OSDDraw_SetAlphaBlending(uwDispID, AHC_FALSE);
	OSDDraw_SetSemiTransparent(uwDispID, AHC_FALSE, AHC_OSD_SEMITP_AVG, 0);
	
	AHC_OSDSetPenSize(uwDispID, 5);
	AHC_OSDSetColor(uwDispID, MENU_BACKGROUND_COLOR);
	AHC_OSDSetBkColor(uwDispID, MENU_BACKGROUND_COLOR);

    AHC_OSDDrawFillRect(uwDispID, 0, 40 , EditFileWindowWidth, 40+EditFileWindowHeight); 

	AHC_OSDSetColor(uwDispID, MENU_TEXT_COLOR);
	AHC_OSDSetBkColor(uwDispID, MENU_BACKGROUND_COLOR);
	if(OutputDevice != MMP_DISPLAY_SEL_MAIN_LCD){
        Rect.x0 = rc.uiLeft;
	    Rect.y0 = rc.uiTop;
	    Rect.x1 = rc.uiLeft + rc.uiWidth;
	    Rect.y1 = rc.uiTop  + rc.uiHeight;
    }else{
        Rect.x0 = rc.uiLeft;
	    Rect.y0 = rc.uiTop;
	    Rect.x1 = STRETCH_W((rc.uiLeft + rc.uiWidth));
	    Rect.y1 = rc.uiTop + rc.uiHeight;	
    }
	
	ShowOSD_SetLanguage(uwDispID);
	
	if(Deleting_InBrowser)
		AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(IDS_DS_MSG_SURE_TO_DELETE_SELETED), 		&Rect, GUI_TA_CENTER|GUI_TA_VCENTER); 	  
	else if(Protecting_InBrowser==1)
		AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(IDS_DS_MSG_SURE_TO_PROTECT_SELETED), 	&Rect, GUI_TA_CENTER|GUI_TA_VCENTER); 	
	else if(Protecting_InBrowser==2)	
		AHC_OSDDrawTextInRect(uwDispID, (UINT8*)OSD_GetStringViaID(IDS_DS_MSG_SURE_TO_UNPROTECT_SELETED), 	&Rect, GUI_TA_CENTER|GUI_TA_VCENTER); 	  
	
	AHC_OSDDrawBitmap(uwDispID, &bmIcon_WMSG, IconX, IconY);
   		
    for( i=0; i<2; i++ )
    {
        GUI_BITMAP barID = BMICON_SMALLBAR_WHITE;

		if(i == CONFIRM_OPT_YES)
    		barID = BMICON_SMALLBAR_YELLOW;

	    DrawSubItem_EditOneFile(uwDispID, i, CONFIRM_MENU_PAGE_ITEM, 
	    						sMenuListDeleteOne[i]->uiStringId, 
	    						sMenuListDeleteOne[i]->bmpIcon, &barID, 
	    						MENU_TEXT_COLOR, MENU_BACKGROUND_COLOR, 0x0);
    }
    
	AHC_OSDSetCurrentDisplay(uwDispID);
	AHC_OSDSetActive(uwDispID, 1);
	
	if(Deleting_InBrowser)
	{
		Delete_File_Confirm = 1;
		Delete_Option = CONFIRM_OPT_YES;
	}
	else if(Protecting_InBrowser==1)
	{
		Protect_File_Confirm = 1;
		Protect_Option = CONFIRM_OPT_YES;	
	}
	else if(Protecting_InBrowser==2)
	{
		UnProtect_File_Confirm = 1;
		UnProtect_Option = CONFIRM_OPT_YES;	
	}
	
    #ifdef FLM_GPIO_NUM
	AHC_OSDRefresh_PLCD();
    #endif
}

void MenuDrawChangeSubItem_EditOneFile(void)
{
    GUI_COLOR 	colorFill 	= MENU_BACKGROUND_COLOR;
    UINT8  		uwDispID 	= MAIN_DISPLAY_BUFFER;
	UINT32 		uiPrevItem;
	UINT32 		uiCurrItem;
	GUI_BITMAP 	barID 		= BMICON_SMALLBAR_WHITE;

	if(Delete_Option==CONFIRM_OPT_YES || Protect_Option==CONFIRM_OPT_YES || UnProtect_Option==CONFIRM_OPT_YES)
	{
		uiPrevItem = CONFIRM_OPT_NO;
		uiCurrItem = CONFIRM_OPT_YES;
	}
	else if(Delete_Option==CONFIRM_OPT_NO || Protect_Option==CONFIRM_OPT_NO || UnProtect_Option==CONFIRM_OPT_NO)
	{
		uiPrevItem = CONFIRM_OPT_YES;
		uiCurrItem = CONFIRM_OPT_NO;
	}
	else
	{
		uiPrevItem = CONFIRM_OPT_NO;
		uiCurrItem = CONFIRM_OPT_YES;
	}

	barID = BMICON_SMALLBAR_WHITE;
	DrawSubItem_EditOneFile(uwDispID, uiPrevItem, CONFIRM_MENU_PAGE_ITEM, 
							sMenuListDeleteOne[uiPrevItem]->uiStringId, 
							sMenuListDeleteOne[uiPrevItem]->bmpIcon, &barID, 
							MENU_TEXT_COLOR, colorFill, 0x0);		
	
	barID = BMICON_SMALLBAR_YELLOW;
	DrawSubItem_EditOneFile(uwDispID, uiCurrItem, CONFIRM_MENU_PAGE_ITEM, 
							sMenuListDeleteOne[uiCurrItem]->uiStringId, 
							sMenuListDeleteOne[uiCurrItem]->bmpIcon, &barID, 
							MENU_TEXT_COLOR, colorFill, 0x0);

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif
}

#if 0
void ________Misc_Function_________(){ruturn;} //dummy
#endif

void DrawProgressBar(UINT32 CurrentIdx, UINT32 MaxIdx, AHC_BOOL bClear)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;    
    UINT16 BarStartX 	= 40;
    UINT16 BarStartY 	= 120;
    UINT32 MaxBarLine;
    UINT32 BarPos;
    UINT16 usDispalyWidth, usDispalyHeight;
    static UINT32  tempBarPos = 0;

    OSDDraw_GetDisplaySize( bID0, &usDispalyWidth, &usDispalyHeight );
    MaxBarLine 	= usDispalyWidth - BarStartX * 2;
    BarPos = (MaxBarLine * CurrentIdx) / MaxIdx;

    if(BarPos == tempBarPos)
        return;

    tempBarPos = BarPos;    
    
	if(AHC_TRUE == AHC_Charger_GetStatus())
		OSDDraw_EnterMenuDrawing(&bID0, &bID1);
	else
    	OSDDraw_GetLastOvlDrawBuffer(&bID0);

	if(bClear)
	{
		//AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
		AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
		AHC_OSDDrawFillRect(bID0, BarStartX-5, BarStartY-5, BarStartX+MaxBarLine+5, BarStartY+5);
	}
	else
	{
		AHC_OSDSetColor(bID0, OSD_COLOR_RED);
		AHC_OSDSetPenSize(bID0, 3);
	      
	    AHC_OSDDrawLine(bID0, BarStartX, 				BarStartX+BarPos, 		BarStartY+2, BarStartY+2);
	    
	    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
	    AHC_OSDSetPenSize(bID0, 1);
	    
	    AHC_OSDDrawLine(bID0, BarStartX, 				BarStartX+MaxBarLine, 	BarStartY, 	 BarStartY);
	    AHC_OSDDrawLine(bID0, BarStartX, 				BarStartX+MaxBarLine, 	BarStartY+5, BarStartY+5);
	    AHC_OSDDrawLine(bID0, BarStartX-1, 				BarStartX-1, 			BarStartY-2, BarStartY+5);
	    AHC_OSDDrawLine(bID0, BarStartX+MaxBarLine+1, 	BarStartX+MaxBarLine+1, BarStartY-2, BarStartY+5);
	}

	if(AHC_TRUE == AHC_Charger_GetStatus())
		OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}