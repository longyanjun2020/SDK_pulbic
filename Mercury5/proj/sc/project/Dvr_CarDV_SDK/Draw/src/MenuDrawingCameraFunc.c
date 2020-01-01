/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_macro.h"
#include "ahc_utility.h"
#include "MenuCommon.h"
#include "IconDefine.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "ShowOSDFunc.h"
#include "DrawStateMenuSetting.h"

/*===========================================================================
 * Main Body
 *===========================================================================*/ 

void DrawSubItem_FlashLevel(UINT16 uwDispID, int iItem, UINT32 iStrID, GUI_BITMAP barID, GUI_COLOR colorFont, GUI_COLOR ColorBack, GUI_COLOR colorSelect)
{
#if (MENU_STILL_FLASH_LEVEL_EN)
    RECT tmpRECT = POS_MENU_FLHIGH , tmpRECT1;

	tmpRECT.uiTop    += ((tmpRECT.uiHeight+18) * iItem);
	
	tmpRECT1.uiLeft   = tmpRECT.uiLeft;
	tmpRECT1.uiTop    = tmpRECT.uiTop ;
	tmpRECT1.uiWidth  = tmpRECT.uiWidth ;
	tmpRECT1.uiHeight = tmpRECT.uiHeight;
	
	OSD_Draw_Icon(barID, tmpRECT1, uwDispID);

	AHC_OSDSetColor(uwDispID, ColorBack);
	
	tmpRECT1.uiLeft   = tmpRECT1.uiLeft 	+ STR_RECT_OFFSET_X; 
	tmpRECT1.uiTop    = tmpRECT1.uiTop 		+ STR_RECT_OFFSET_Y; 
	tmpRECT1.uiWidth  = tmpRECT1.uiWidth 	+ STR_RECT_OFFSET_W; 
	tmpRECT1.uiHeight = tmpRECT1.uiHeight 	+ STR_RECT_OFFSET_H;
	
	OSD_ShowStringPool(uwDispID, iStrID, tmpRECT1, colorFont, ColorBack, GUI_TA_HCENTER|GUI_TA_VCENTER);
#endif
}

void MenuDrawSubPage_FlashLevel(PSMENUSTRUCT pMenu)
{
#if (MENU_STILL_FLASH_LEVEL_EN)

    UINT8  bID0 = 0, bID1 = 0;
    UINT32 i;
    UINT32 iBegin, iEnd;

    OSDDraw_EnterMenuDrawing(&bID0, &bID1);
    
    OSDDraw_ClearOvlDrawBuffer(bID0);

    iBegin = ALIGN_DOWN( pMenu->iCurrentPos, SUB_MENU_PAGE_ITEM );
    iEnd   = MIN( iBegin+SUB_MENU_PAGE_ITEM, pMenu->iNumOfItems);

	MenuDrawSubBackCurtain(bID0, OSD_COLOR_BACKGROUND);

	if( pMenu->uiStringId != -1 )
	{
		MenuDrawSubTitle(bID0, pMenu->uiStringId);
	}

    for( i=iBegin; i< iEnd; i++ )
    {
        GUI_COLOR  clrBk = OSD_COLOR_TRANSPARENT;
        GUI_BITMAP barID = BMICON_MENUBAR_WHITE;

        if(pMenu->iNumOfItems > 1 )
        {
            if(( i == pMenu->iCurrentPos ) && ( i != pMenu->pfMenuGetDefaultVal(pMenu) ))
            {
    		    barID = BMICON_MENUBAR_YELLOW;
            }
            else if(( i == pMenu->iCurrentPos ) && ( i == pMenu->pfMenuGetDefaultVal(pMenu) ))
            {
    		    barID = BMICON_MENUBAR_YELLOW_DEFAULT;
            }
            else if(( i != pMenu->iCurrentPos ) && ( i == pMenu->pfMenuGetDefaultVal(pMenu) ))
            {
    		    barID = BMICON_MENUBAR_WHITE_DEFAULT;
            }
		}
        else // if(pMenu->iNumOfItems ==1 )
            barID = BMICON_MENUBAR_YELLOW;

        DrawSubItem_FlashLevel(bID0, i, pMenu->pItemsList[i]->uiStringId, barID, MENU_TEXT_COLOR, clrBk, 0x0);
    }

    if(pMenu->uiStringDescription != NULL)
    	MenuDrawSubMenuDescription(bID0, pMenu->uiStringDescription);
    
	MenuDraw_BatteryStatus(bID0);

	OSDDraw_ExitMenuDrawing(&bID0, &bID1);
#endif	
}

void MenuDrawChangeSubItem_FlashLevel(PSMENUSTRUCT pMenu, UINT32 uiCurrItem, UINT32 uiPrevItem, UINT32 uiPreSelected)
{
#if (MENU_STILL_FLASH_LEVEL_EN)

    UINT8     bID0 = 0, bID1 = 0;

    GUI_COLOR clrFill   = OSD_COLOR_TRANSPARENT;
    GUI_COLOR clrSelect = 0x0;

	OSDDraw_EnterMenuDrawing(&bID0, &bID1);

	if( pMenu->iSelected == uiPrevItem )
		clrSelect = OSD_COLOR_SELECTED;
    else
		clrSelect = 0;

    //Draw Previous
    if( ( pMenu->uiStatus == MENU_STATUS_PRESSED ) ||( uiPrevItem != pMenu->pfMenuGetDefaultVal(pMenu)) )
    {
    	DrawSubItem_FlashLevel(bID0, uiPrevItem%SUB_MENU_PAGE_ITEM,  pMenu->pItemsList[uiPrevItem]->uiStringId, BMICON_MENUBAR_WHITE, MENU_TEXT_COLOR, clrFill, clrSelect);
    }
    else if ( uiPrevItem == pMenu->pfMenuGetDefaultVal(pMenu))
    {
    	DrawSubItem_FlashLevel(bID0, uiPrevItem%SUB_MENU_PAGE_ITEM,  pMenu->pItemsList[uiPrevItem]->uiStringId, BMICON_MENUBAR_WHITE_DEFAULT, MENU_TEXT_COLOR, clrFill, clrSelect);
    }

    if(uiPreSelected /SUB_MENU_PAGE_ITEM == uiCurrItem /SUB_MENU_PAGE_ITEM )
    {
		if( pMenu->iSelected == uiPreSelected )
			clrSelect = OSD_COLOR_SELECTED;
	    else
			clrSelect = 0;
		    
		//Draw PreSelected
        if(( pMenu->uiStatus == MENU_STATUS_PRESSED ) ||( uiPreSelected != pMenu->pfMenuGetDefaultVal(pMenu)))
        {
			DrawSubItem_FlashLevel(bID0, uiPreSelected,  pMenu->pItemsList[uiPreSelected]->uiStringId, BMICON_MENUBAR_WHITE, MENU_TEXT_COLOR, clrFill, clrSelect);
        }
        else if( uiPreSelected == pMenu->pfMenuGetDefaultVal(pMenu))
        {
			DrawSubItem_FlashLevel(bID0, uiPreSelected,  pMenu->pItemsList[uiPreSelected]->uiStringId, BMICON_MENUBAR_WHITE_DEFAULT, MENU_TEXT_COLOR, clrFill, clrSelect);
        }
	}

    if( pMenu->iSelected == uiCurrItem )
		clrSelect = OSD_COLOR_SELECTED;
    else
		clrSelect = 0;
	
	//Draw current
	if( uiCurrItem == pMenu->pfMenuGetDefaultVal(pMenu))
	    DrawSubItem_FlashLevel(bID0, uiCurrItem, pMenu->pItemsList[uiCurrItem]->uiStringId, BMICON_MENUBAR_YELLOW_DEFAULT, MENU_TEXT_COLOR,  clrFill, clrSelect);
    else
	    DrawSubItem_FlashLevel(bID0, uiCurrItem, pMenu->pItemsList[uiCurrItem]->uiStringId, BMICON_MENUBAR_YELLOW, MENU_TEXT_COLOR,  clrFill, clrSelect);
           
	OSDDraw_ExitMenuDrawing(&bID0, &bID1);
#endif	
}

