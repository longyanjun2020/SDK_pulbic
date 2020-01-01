#ifndef _MENU_TOUCH_BUTTON_H_
#define _MENU_TOUCH_BUTTON_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "MenuCommon.h"

/*===========================================================================
 * Macro define 
 *===========================================================================*/ 

/**	@brief	check the point is in the rectangle or not. */
#define     IS_POINT_IN_RECT(PT, RC)          (	( (PT).PointX >= (RC).uiLeft ) && ( (PT).PointY >= (RC).uiTop  ) && ( (PT).PointX <= (RC).uiLeft + (RC).uiWidth ) && ( (PT).PointY <= (RC).uiTop  + (RC).uiHeight )  )
/**	@brief	the number of touch button. */
#define     ITEMNUM(x)                        (sizeof(x)/sizeof(SMENUTOUCHBUTTON))

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 

typedef enum _TouchPage{
   	TOUCH_MAIN_PAGE,
    TOUCH_CTRL_PAGE
}TouchPage;

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

void 		AhcClearTouchButton(void);
AHC_BOOL 	AhcAddedTouchButton( PSMENUTOUCHBUTTON pButton );
UINT32 		AhcCheckTouchButton( PPOINT pPoint, AHC_BOOL bMove );
UINT32 		AhcCheckTouchButtonEx(PSMENUSTRUCT pMenu, PPOINT pPoint, AHC_BOOL bMove );
UINT32		AhcCheckTBitem(PSMENUITEM* pit, PPOINT pPoint, AHC_BOOL bMove );
UINT32 		AhcGetLastTouchButton(void);
void KeyParser_AddTouchOffset(PSMENUTOUCHBUTTON pButton);
void KeyParser_ResetTouchVariable(void);
void KeyParser_GetTouchPoint(UINT32 ulParam, PPOINT pPoint);
void KeyParser_TouchItemRegister(SMENUTOUCHBUTTON *pButton, UINT8 ItemNum);

#endif
