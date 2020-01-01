/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_utility.h"
#include "ahc_macro.h"
#include "ahc_os.h"
#include "ahc_parameter.h"
#include "ahc_general.h"
#include "ahc_menu.h"
#include "ahc_warningmsg.h"
#include "IconDefine.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "MenuCommon.h"
#include "MenuDrawingFunc.h"
#include "MenuStateMenu.h"
#include "MenuDrawCommon.h"
#include "MenuSetting.h"
#include "DrawStateMenuSetting.h"
#include "ShowOSDFunc.h"
#include "statehdmifunc.h"
#include "statetvfunc.h"
#include "dsc_charger.h"
#include "MenuStateMisc.h"

/*===========================================================================
 * Extern varible
 *===========================================================================*/


/*===========================================================================
 * Main body
 *===========================================================================*/ 

#if 0
void ________SlideMenu_Function_________(){ruturn;} //dummy
#endif

#ifdef SLIDE_MENU

typedef struct {
	UINT32 		mXPos;
	INT32		mXOffset;	
	UINT8		mbShow;			// 0:Dismiss, 1:Show
	UINT8		mbEnable;
} SLIDE_SMENU;

SLIDE_SMENU SlideMenu;

void StartSlideMenu(UINT32 ulXpos, INT32 ulXoff, UINT8 ubShow, UINT8 ubEn)
{
	SlideMenu.mXPos 	= ulXpos;
	SlideMenu.mXOffset 	= ulXoff;
	SlideMenu.mbShow 	= ubShow;
	SlideMenu.mbEnable 	= ubEn;
}

void StopSlideMenu(void)
{
	SlideMenu.mbEnable 	= 0;
}

UINT8 IsSlidingMenu(void)
{
	return SlideMenu.mbEnable;
}

void SetSlidingMenuEn(UINT8 bEn)
{
	SlideMenu.mbEnable = bEn;
}

UINT32 GetSlideXPostion(void)
{
	return SlideMenu.mXPos;
}

void SlideSubMenu(void)
{
}

#endif

#if 0
void ________SlideString_Function_________(){ruturn;} //dummy
#endif

#ifdef SLIDE_STRING
/*
 * SLIDE STRING for some string that length is larger then rect
 */
typedef struct {
	int			mDisp;
	int			mSlide;
	int			mOff;
	UINT32		mStr;
	RECT		mStrRC;
	GUI_BITMAP	mBar;
	RECT		mBarRC;
	GUI_COLOR	mClrFnt;
	GUI_COLOR	mClrBak;
} SLIDE_STR;

#define	START_CNT	(20)
#define	SS_NUM		(6)

SLIDE_STR	theSS[SS_NUM] = { 0 };

int IsSlideSting(UINT32 idStr)
{
	int		i;
	int		slide;
	
	slide = 0;
	
	for (i = 0; i < SS_NUM; i++) 
	{
		if (theSS[i].mSlide && theSS[i].mStr == idStr) 
		{
			slide = theSS[i].mOff;
		
			if (slide > START_CNT) {
				slide -= START_CNT;
			} else {
				slide = 0;
			}
		}
	}
	return slide;
}
/*
 * Enable Slide sting for isStr
 */
int StartSlideString(UINT16 uwDisplayID,
					 UINT32 idStr, RECT strrc,
					 GUI_BITMAP bar, RECT barrc,
					 GUI_COLOR clrfnt, GUI_COLOR clrbak,
					 int slide)
{
	int	i;
	
	for (i = 0; i < SS_NUM; i++) 
	{
		if (theSS[i].mSlide && theSS[i].mStr == idStr) 
		{
			// Turn off awhile
			theSS[i].mSlide = 0;
			theSS[i].mStrRC = strrc;
			theSS[i].mBar   = bar;
			theSS[i].mBarRC = barrc;
			theSS[i].mDisp  = uwDisplayID;
			theSS[i].mClrFnt= clrfnt;
			theSS[i].mClrBak= clrbak;
			// Turn on
			theSS[i].mSlide = slide;
			return i;
		}
	}
	
	for (i = 0; i < SS_NUM; i++) 
	{
		if (theSS[i].mSlide == 0) 
		{
			theSS[i].mSlide = slide;
			theSS[i].mStr   = idStr;
			theSS[i].mStrRC = strrc;
			theSS[i].mBar   = bar;
			theSS[i].mBarRC = barrc;
			theSS[i].mOff   = 0;
			theSS[i].mDisp  = uwDisplayID;
			theSS[i].mClrFnt= clrfnt;
			theSS[i].mClrBak= clrbak;
			return i;
		}
	}
	return -1;
}

/*
 * Call by timer to slide string
 */
void SlideString(void)
{
    int			i;
    int			update = 0;
    UINT8     	bID0 = 0;
    UINT8     	bID1 = 0;
    
    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

	for (i = 0; i < SS_NUM; i++) 
	{
		if (theSS[i].mSlide != 0) 
		{
			int		slide;
			
			slide = ++theSS[i].mOff;
		
			if (slide < START_CNT && slide != 0) 
				continue;
				
			if (update == 0) {
				update = 1;
				OSDDraw_EnterMenuDrawing(&bID0, &bID1);
			}
			
			if (slide != 0) 
				slide -= START_CNT;

            BEGIN_LAYER(bID0);

			OSD_Draw_Icon(theSS[i].mBar, theSS[i].mBarRC, bID0);
			AHC_OSDSetColor(bID0, theSS[i].mClrBak);
			OSD_ShowStringPoolSlide(bID0, theSS[i].mStr, theSS[i].mStrRC,
									theSS[i].mClrFnt, theSS[i].mClrBak,
									GUI_TA_HCENTER|GUI_TA_VCENTER, &slide);

            END_LAYER(bID0);

			if (slide == 0) 
			{
				theSS[i].mOff = -START_CNT; //theSS[i].mOff [Max]: START_CNT+ max remain pixel [Min]:-START_CNT
			}	
		}
	}
	
	if (update) 
	{
	    OSDDraw_SetAlphaBlending(bID0, AHC_TRUE);
	    OSDDraw_SetAlphaBlending(bID1, AHC_TRUE);
		OSDDraw_ExitMenuDrawing(&bID0, &bID1);
	}
}

/*
 * Stop All of Slide String
 */
void StopSlideString(void)
{
	int	i;
	
	for (i = 0; i < SS_NUM; i++) {
		theSS[i].mSlide = 0;
	}
}

void StopSlideStringIdx(UINT8 idx)
{
	theSS[idx].mSlide = 0;
}

int GetSlideStringIdx(UINT32 idStr)
{
	int	i;
		
	for (i = 0; i < SS_NUM; i++) 
	{
		if (theSS[i].mStr == idStr) 
			return i;
	}
	
	return 0xFF;
}

#endif	// SLIDE_STRING
