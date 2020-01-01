/*****************************************************************************************
* @bjxapp_view.h
*
* Comment: 
*
* @version:0.0.2  @ 2009.12.01 
*****************************************************************************************/
#ifndef __bjxapp_view__H
#define __bjxapp_view__H
#include "mmi_common_wdgvar.h"
#include "mmi_bjxapp_priv.h"

#ifdef __TOUCH_SCREEN_MMI__

typedef struct
{
    IWidget *pSurnameGrid;
    IWidget *pSurnameItem;
    IWidget *pAlphabetBgCnt;
    IWidget *pAlphabetGrid;
    IWidget *pAlphabetItem;
} BjxAppMainViewWdgList_t;

MAE_Ret BjxAppCreateMainView(HWIN hWin, BjxAppMainViewWdgList_t *pWdgList);
//*******************************************************************//
#endif // __TOUCH_SCREEN_MMI__
#endif //__bjxapp_view__H
