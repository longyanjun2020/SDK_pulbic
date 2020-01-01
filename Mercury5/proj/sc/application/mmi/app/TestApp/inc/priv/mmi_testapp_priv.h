/**
* @file mmi_helloworld_priv.h
**/

#ifndef __MMI_HELLOWORLD_PRIV_H__
#define __MMI_HELLOWORLD_PRIV_H__

//////////////////////////////////////////////////////////////////////////
//==========Includes======================= 
#include "mmi_baseapplet.h"
//==========Types&Data=====================
/**
 * Application structure
 */

enum
{
	WDG_TEST_ABSCONTAINER = 0,
	WDG_TEST_ALIVE ,
	WDG_TEST_BASICBITMAP ,
	WDG_TEST_BASICDESKTOP ,
	WDG_TEST_BITMAP ,
	WDG_TEST_BUTTON ,
	WDG_TEST_CALENDARDESKTOP ,
	WDG_TEST_DATE ,
	WDG_TEST_DATEICON ,
	WDG_TEST_DCLOCKDESKTOP ,
	WDG_TEST_DOUBLEITEM ,
	WDG_TEST_DUMMY ,
	WDG_TEST_DYNAMICMENU ,
	WDG_TEST_EVENT ,
	WDG_TEST_FADEOUT ,
	WDG_TEST_FCDATE ,
	WDG_TEST_FCTIME ,
	WDG_TEST_FMDESKTOP ,
	WDG_TEST_IMAGE ,
	WDG_TEST_IMAGEDOUBLE ,
	WDG_TEST_IMAGETEXTIMAGE ,
	WDG_TEST_INDICATOR ,
	WDG_TEST_IME  ,
	WDG_TEST_INPUT,
	WDG_TEST_IP ,
	WDG_TEST_LIST ,
	WDG_TEST_MENU ,
	WDG_TEST_MFCONTAINER ,
	WDG_TEST_MPDESKTOP ,
	WDG_TEST_NOTEDESKTOP ,
	WDG_TEST_OPDESKTOP ,
	WDG_TEST_OSD ,
	WDG_TEST_PICK ,
	WDG_TEST_PICKCOMMON ,
	WDG_TEST_POPSELECT ,
	WDG_TEST_PROFILE ,
	WDG_TEST_PROGRESS ,
	WDG_TEST_PROPCONTAINER ,
	WDG_TEST_PULLDOWN,
	WDG_TEST_RINGLIST ,
	WDG_TEST_SCROLLBAR ,
	WDG_TEST_SCROLLINDICATOR ,
	WDG_TEST_SEARCHDESKTOP  ,
	WDG_TEST_SHEETCONTAINER ,
	WDG_TEST_SHORTCUTBAR ,
	WDG_TEST_SLIDESWITCH ,
	WDG_TEST_SOFTKEY ,
	WDG_TEST_STATISTIC ,
	WDG_TEST_STATICMENU ,
	WDG_TEST_STATUSBAR ,
	WDG_TEST_SWITCHICON ,
	WDG_TEST_SWITCHICONITEM ,
	WDG_TEST_TEXT ,
	WDG_TEST_TAB ,
	WDG_TEST_THMTEXT ,
	WDG_TEST_TIME ,
	WDG_TEST_TIMEFORMAT ,
	WDG_TEST_TITLE ,
	WDG_TEST_TRANSITION ,
	WDG_TEST_VIEWCONTAINER ,
	WDG_TEST_VIEWPORT ,
	WDG_TEST_VOLUME ,
	WDG_TEST_MAX
};

typedef struct MMI_HELLOWORLD_t_ 
{
	APPLET_BASE_ELEMENTS;

	IWidget* pTestWdg1;

	HWIN hWin;

	u32 nViewNum;
	u32 *Table[WDG_TEST_MAX];
	u32 nCurrentWdgID;

} MMI_HELLOWORLD;
//////////////////////////////////////////////////////////////////////////

typedef struct WndData_t_
{
    IView* pIView;
}WndData_t;

//////////////////////////////////////////////////////////////////////////
//[NeedToCheck]
typedef enum HelloworldWndId_e_
{
    HELLOWORLD_WND_MAIN = 1,//WND_ID_APP_BASE,
	HELLOWORLD_WND_SUB
}HelloworldWndId_e;

//////////////////////////////////////////////////////////////////////////
//==========Function=======================
//New function.
//[NeedToCheck]
MAE_Ret _HelloworldEntryMain(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _HelloworldExitMain(void* pCusHandle,void* pWndData);
MAE_Ret _HelloworldEntrySub(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _HelloworldExitSub(void* pCusHandle,void* pWndData);
MAE_Ret _HelloWorldStartCB(IApplet* pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret _HelloWorldStopCB(IApplet* pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret _TestMenuStartCB(IApplet* pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret _HelloWorldKeyPressCB(IApplet* pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
//MAE_Ret _HelloWorldWndHandler(void* pWndHandle, WindowMsg_t *pWndMsg, void* pWndData, u32 nInitParam);

#endif /* __MMI_HELLOWORLD_PRIV_H__ */
