/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_audio.h"
#include "ahc_utility.h"
#include "ahc_macro.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "IconDefine.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "MenuDrawCommon.h"
#include "MenuDrawingFunc.h"
#include "ShowOSDFunc.h"
#include "DrawStateMenuSetting.h"
#include "statehdmifunc.h"
#include "ahc_display.h"

/*===========================================================================
 * Main body
 *===========================================================================*/

void MenuDrawSubButtons_Volume(UINT16 uwDispID)
{
	UINT16 x1 = POS_MENU_VOL_DEC_X;
	UINT16 x2 = POS_MENU_VOL_INC_X;
	
	if(AHC_IsHdmiConnect())
	{
		if(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080P)
		{
			x1 += 50;
			x2 += 50;
		}
		else
		{
			x1 += 50;
			x2 += 50;
		}	
	}	
	
	OSD_Draw_IconXY(uwDispID, bmIcon_Volume_Decrease, x1, POS_MENU_VOL_DEC_Y);
	OSD_Draw_IconXY(uwDispID, bmIcon_Volume_Increase, x2, POS_MENU_VOL_INC_Y);
	#if (SUPPORT_TOUCH_PANEL)
	OSD_Draw_IconXY(uwDispID, bmIcon_OK, 			  POS_MENU_EV_OK_X,  POS_MENU_EV_OK_Y);
	#endif

}

void DrawSubItem_ShowVolume(UINT16 uwDispID, int iItem)
{
}

void DrawSubItem_Volume(UINT16 uwDispID, int iItem, int iTotalItems, UINT32 iStrID, const GUI_BITMAP* IconID, UINT32 barState, GUI_COLOR clrFont, GUI_COLOR clrBack, GUI_COLOR clrSelect)
{
    RECT 		rc = RECT_MENU_VOL_ITEM;
    GUI_COLOR 	FillColor;

	rc.uiLeft 	+= ( rc.uiWidth + 5 ) * iItem;
	rc.uiTop  	-= 2 * iItem;
	rc.uiHeight += 4 * iItem;
	
	if(AHC_IsHdmiConnect())
	{
		if(MenuSettingConfig()->uiHDMIOutput == HDMI_OUTPUT_1080P)
		{
			rc.uiLeft += 50;
		}
		else
		{
			rc.uiLeft += 50;
		}	
	}

    FillColor = 0xFF111111;

    if( clrSelect != 0 )
        FillColor = clrSelect;

    AHC_OSDSetColor(uwDispID, OSD_COLOR_BLACK);
    AHC_OSDDrawRect2(uwDispID, &rc);

    AHC_OSDSetColor(uwDispID, FillColor);
    AHC_OSDDrawFillRect(uwDispID, rc.uiLeft+1, rc.uiTop+1, rc.uiLeft+rc.uiWidth-1, rc.uiTop+rc.uiHeight-1);
}

void MenuDrawSubPage_Volume(PSMENUSTRUCT pMenu)
{
    UINT8  	bID0 = 0;
    UINT8  	bID1 = 0;
    UINT32 	i;
    
#ifdef SLIDE_STRING
	StopSlideString();
#endif

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);
    
    OSDDraw_ClearOvlDrawBuffer(bID0);
    
	MenuDrawSubBackCurtain(bID0, MENU_BACKGROUND_COLOR);

    MenuDrawSubButtons_Volume(bID0);

    for( i=0; i< pMenu->iNumOfItems-1; i++ )
    {
        GUI_COLOR clrSelect = 0x0;

        if( pMenu->pfMenuGetDefaultVal(pMenu) > 0) 
        {
            if ( i <= pMenu->pfMenuGetDefaultVal(pMenu)-1 ) 
            {
                clrSelect = OSD_COLOR_GREEN;
            } 
        }

        DrawSubItem_Volume(	bID0, i, pMenu->iNumOfItems, 
                			pMenu->pItemsList[i]->uiStringId, 
        					pMenu->pItemsList[i]->bmpIcon,
        					NULL,
        					MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, clrSelect);
    }

    if(pMenu->uiStringId != -1)
        MenuDrawSubTitle(bID0, pMenu->uiStringId);

    if(pMenu->uiStringDescription != NULL)
    	MenuDrawSubMenuDescription(bID0, pMenu->uiStringDescription);

	MenuDraw_BatteryStatus(bID0);

    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
    
}

void MenuDrawChangeSubItem_Volume(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
    UINT8 		bID0 = 0, bID1 = 0;
	GUI_COLOR	clrSelect = 0x0;

	OSDDraw_EnterMenuDrawing(&bID0, &bID1);

	if ( uiPrevItem <= uiCurrItem && uiCurrItem > 1)      
	{
		clrSelect = OSD_COLOR_GREEN;
	}

	//Draw Previous
	if(uiPrevItem == 0)
		DrawSubItem_Volume(	bID0, uiPrevItem, pMenu->iNumOfItems, 
							pMenu->pItemsList[uiPrevItem]->uiStringId, 
        					pMenu->pItemsList[uiPrevItem]->bmpIcon,
        					NULL,
							MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, clrSelect);
	else 
		DrawSubItem_Volume(	bID0, uiPrevItem-1, 	pMenu->iNumOfItems,  
							pMenu->pItemsList[uiPrevItem]->uiStringId, 
        					pMenu->pItemsList[uiPrevItem]->bmpIcon,
        					NULL,
							MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, clrSelect); 
	//Draw current
	if(uiCurrItem == 0)
		DrawSubItem_Volume(	bID0, uiCurrItem, pMenu->iNumOfItems, 
							pMenu->pItemsList[uiCurrItem]->uiStringId, 
        					pMenu->pItemsList[uiCurrItem]->bmpIcon,
        					NULL,
							MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, 0x0); 
	else 
		DrawSubItem_Volume(	bID0, uiCurrItem-1, pMenu->iNumOfItems, 
							pMenu->pItemsList[uiCurrItem]->uiStringId, 
        					pMenu->pItemsList[uiCurrItem]->bmpIcon,
        					NULL,
							MENU_TEXT_COLOR, OSD_COLOR_TRANSPARENT, OSD_COLOR_GREEN);
          
    OSDDraw_ExitMenuDrawing(&bID0, &bID1);
}
