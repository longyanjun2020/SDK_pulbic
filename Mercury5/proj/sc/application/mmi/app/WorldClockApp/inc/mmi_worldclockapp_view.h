/*****************************************************************************************
* @worldclockapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __worldclockapp_view__H
#define __worldclockapp_view__H


typedef struct
{
    IWidget *pIMapBgImageWdg;
    IWidget *pILineImageWdg;
    IWidget *pICityImageWdg;
    IWidget *pITzTextWdg;
    IWidget *pITimeTextWdg;
} WorldClockAppMainViewWdgList_t;

MAE_Ret _WorldClockAppCreateMainView(HWIN hWin, WorldClockAppMainViewWdgList_t *pWdgList);
 MAE_Ret _WorldClockAppSetWnd(void *pCusHandle, WorldClockAppMainViewWdgList_t *pWdgList);

//*******************************************************************//
#endif //__worldclockapp_view__H
