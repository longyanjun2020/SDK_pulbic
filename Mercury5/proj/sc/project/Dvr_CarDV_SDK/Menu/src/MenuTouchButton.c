/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "MenuCommon.h"
#include "MenuTouchButton.h"
#include "IconPosition.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#if (SUPPORT_TOUCH_PANEL==1)

#define  MAX_TOUCH_BUTTON        (32)
#define  TOUCH_OTHER_AREA		 (60)
/*===========================================================================
 * Global variable
 *===========================================================================*/

static SMENUTOUCHBUTTON	sMenuTouchButtons[MAX_TOUCH_BUTTON];///< the attribute of touch button.
static int				iNumOfTouchButton	= 0;			///< the number of touch button.
static UINT32			tEvent				= MENU_NONE;	///< the last status of touch button.

AHC_BOOL   				bIconCaptPressed 	= AHC_FALSE;
AHC_BOOL   				bIconRecPressed 	= AHC_FALSE;
AHC_BOOL   				bIconWidePressed 	= AHC_FALSE;
AHC_BOOL   				bIconTelePressed 	= AHC_FALSE;
AHC_BOOL   				bIconZoomPressed 	= AHC_FALSE;
AHC_BOOL   				bIconPageSwitch 	= AHC_FALSE;
AHC_BOOL   				bIconNextPressed 	= AHC_FALSE;
AHC_BOOL   				bIconPrevPressed 	= AHC_FALSE;

/*===========================================================================
 * Main body
 *===========================================================================*/

/**	@brief	add a new touch button. */
AHC_BOOL AhcAddedTouchButton( PSMENUTOUCHBUTTON pButton )
{
    if(iNumOfTouchButton < MAX_TOUCH_BUTTON )
    {
        sMenuTouchButtons[iNumOfTouchButton] = *pButton;
        iNumOfTouchButton++;
    }
    return AHC_FALSE;
}

/**	@brief clear the attribute of all the touch buttons. */
void AhcClearTouchButton(void)
{
    iNumOfTouchButton = 0;
    memset( &sMenuTouchButtons, 0, sizeof(sMenuTouchButtons) );
}

/**	@brief	translate the position of touch point to the attribute of touch button. */
UINT32 AhcCheckTouchButton( PPOINT pPoint, AHC_BOOL bMove )
{
    POINT   pt = *pPoint;
    int     i;

    for( i = 0 ; i < iNumOfTouchButton ; i++ )
    {
        if( IS_POINT_IN_RECT( pt, sMenuTouchButtons[i].rcButton ) )
        {
            tEvent = (bMove) ? sMenuTouchButtons[i].ulOpTouchMove : sMenuTouchButtons[i].ulOpTouch;
            //printc("[ AhcCheckTouchButton ]i %d   tEvent 0x%X",i, tEvent);
			if(tEvent == NULL)
			{
				if(sMenuTouchButtons[i].pTouchCallBack != NULL)
					tEvent = sMenuTouchButtons[i].pTouchCallBack(pt.PointX,pt.PointY);				
			}
            return tEvent;
        }
    }
    /**	@brief	can not get one touch button. */
    tEvent = MENU_NONE;
    return tEvent;
}

/*
 * return:
 *	HIWORD is NO. item
 *	LOWORD is Event ID
 */
#define	PT_IN_RECT(p, rc) ((signed short)((p).PointX) >= (signed short)((rc).uiLeft) &&					\
						   (signed short)((p).PointX) <= (signed short)((rc).uiLeft + (rc).uiWidth) &&	\
						   (signed short)((p).PointY) >= (signed short)((rc).uiTop) &&					\
						   (signed short)((p).PointY) <= (signed short)((rc).uiTop + (rc).uiHeight))
UINT32 AhcCheckTouchButtonEx(PSMENUSTRUCT pMenu, PPOINT pPoint, AHC_BOOL bMove )
{
	int					i;
	PSMENUITEM			*pit;

	pit = pMenu->pItemsList;
	for( i = 0 ; i < pMenu->iNumOfItems ; i++) {
		SMENUTOUCHBUTTON	*pmb;
		RECT				spot;

		pmb  = pit[i]->ptp;
		spot = pmb->rcButton;
		spot.uiLeft   -= pmb->ubOpTouchOffset;
		spot.uiTop    -= pmb->ubOpTouchOffset;
		spot.uiWidth  += pmb->ubOpTouchOffset;
		spot.uiHeight += pmb->ubOpTouchOffset;
		if (PT_IN_RECT(*pPoint, spot)) {
			return (bMove) ? (pmb->ulOpTouchMove + (i << 16)) :
							 (pmb->ulOpTouch + (i << 16));
		}
	}
	return TOUCH_OTHER_AREA;
}

UINT32 AhcCheckTBitem(PSMENUITEM* pit, PPOINT pPoint, AHC_BOOL bMove )
{
	int					i;

	for( i = 0 ; pit[i] != NULL; i++) {
		SMENUTOUCHBUTTON	*pmb;
		RECT				spot;

		pmb  = pit[i]->ptp;
		spot = pmb->rcButton;
		spot.uiLeft   -= pmb->ubOpTouchOffset;
		spot.uiTop    -= pmb->ubOpTouchOffset;
		spot.uiWidth  += pmb->ubOpTouchOffset;
		spot.uiHeight += pmb->ubOpTouchOffset;
		if (PT_IN_RECT(*pPoint, spot)) {
			return (bMove) ? (pmb->ulOpTouchMove) : (pmb->ulOpTouch);
		}
	}
	return TOUCH_OTHER_AREA;
}

/**	@brief get the last status of touch button. */
UINT32 AhcGetLastTouchButton(void)
{
    return tEvent;
}

void KeyParser_AddTouchOffset(PSMENUTOUCHBUTTON pButton)
{
	/**	@brief	the top-left positon (horizontal) */
    if( pButton->rcButton.uiLeft > pButton->ubOpTouchOffset)
    {
        pButton->rcButton.uiWidth += pButton->ubOpTouchOffset;
        pButton->rcButton.uiLeft  -= pButton->ubOpTouchOffset;
    }
    else
    {
        pButton->rcButton.uiWidth += pButton->rcButton.uiLeft;
        pButton->rcButton.uiLeft   = 0;
	}
	/**	@brief	the top-right positon (horizontal) */
    if( (pButton->rcButton.uiLeft+pButton->rcButton.uiWidth+pButton->ubOpTouchOffset) < DISP_WIDTH )
    {
        pButton->rcButton.uiWidth += pButton->ubOpTouchOffset;
	}
	else
	{
        pButton->rcButton.uiWidth = DISP_WIDTH - pButton->rcButton.uiLeft;
	}
	/**	@brief	the top-left positon (vertical) */
    if( pButton->rcButton.uiTop > pButton->ubOpTouchOffset )
    {
        pButton->rcButton.uiHeight += pButton->ubOpTouchOffset;
        pButton->rcButton.uiTop    -= pButton->ubOpTouchOffset;
    }
    else
    {
        pButton->rcButton.uiHeight += pButton->rcButton.uiTop;
        pButton->rcButton.uiTop     = 0;
	}
	/**	@brief	the bottom-left positon (vertical) */
    if( (pButton->rcButton.uiTop+pButton->rcButton.uiHeight+pButton->ubOpTouchOffset) < DISP_HEIGHT )
    {
        pButton->rcButton.uiHeight += pButton->ubOpTouchOffset;
	}
	else
	{
        pButton->rcButton.uiHeight = DISP_HEIGHT - pButton->rcButton.uiTop;
	}
}

/**	@brief reset the status of touch button. */
void KeyParser_ResetTouchVariable(void)
{
    bIconCaptPressed = AHC_FALSE;
    bIconRecPressed  = AHC_FALSE;
    bIconWidePressed = AHC_FALSE;
    bIconTelePressed = AHC_FALSE;
    bIconZoomPressed = AHC_FALSE;
    bIconNextPressed = AHC_FALSE;
    bIconPrevPressed = AHC_FALSE;
}

void KeyParser_GetTouchPoint(UINT32 ulParam, PPOINT pPoint)
{
    pPoint->PointX = ulParam & 0xFFFF;
    pPoint->PointY = (ulParam >> 16) & 0xFFFF;
}

/**	@brief	initialize the attribute of touch button. */
void KeyParser_TouchItemRegister(SMENUTOUCHBUTTON *pButton, UINT8 ItemNum)
{
    UINT8 n = 0;
    SMENUTOUCHBUTTON tButton;

    AhcClearTouchButton();

    for(n = 0; n < ItemNum; n++)
    {
        tButton = *(pButton + n);
        //KeyParser_AddTouchOffset(&tButton);
        AhcAddedTouchButton(&tButton);
    }
}

#endif
