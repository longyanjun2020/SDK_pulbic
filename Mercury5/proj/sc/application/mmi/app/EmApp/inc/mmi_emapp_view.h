/*****************************************************************************************
* @emapp_view.h
*
* Comment: 
*
* @version:0.0.2  @ 2009.12.01 
*****************************************************************************************/
#ifndef __emapp_view__H
#define __emapp_view__H

#include "mmi_emapp_priv.h"
#include "mmi_common_wdgvar.h"
#include "mae_textlabel.h"

typedef struct
{
    IWidget *pMenuWdg;
}EmAppMainListViewWdgList_t;

MAE_Ret EmAppCreateMainListView(HWIN hWin, EmAppMainListViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pMainContainer;
    IWidget *pScrollBarWidget;
    IWidget *pInputWidget;
    IWidget *pButtonWdgPropContainer;
    IWidget *pSendKeyButtonWidget;
    IWidget *pEndKeyButtonWidget;
}EmAppDisplayAutoTestResultViewWdgList_t;

MAE_Ret EmAppCreateDisplayAutoTestResultView(HWIN hWin, EmAppDisplayAutoTestResultViewWdgList_t *pWdgList);
MAE_Ret EmAppSetDisplayAutoTestResultView(HWIN hWin, EmAppDisplayAutoTestResultViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pInputWdg;
    IWidget *pTitleWdg;
}EmAppEditViewWdgList_t;

MAE_Ret EmAppCreateEditView(HWIN hWin, EmAppEditViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
}EmAppMenuHistoryViewWdgList_t;

MAE_Ret EmAppCreateMenuHistoryView(HWIN hWin, EmAppMenuHistoryViewWdgList_t *pWdgList, boolean bRadio);

//*******************************************************************//

typedef struct
{
    IWidget *pInputWdg;
    IWidget *pTitleWdg;
}EmAppAsyncInfoViewWdgList_t;

MAE_Ret EmAppCreateAsyncInfoView(HWIN hWin, EmAppAsyncInfoViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pInputWdg;
    IWidget *pTitleWdg;
    IWidget *pLcdBmpWdg;
}EmAppSyncInfoViewWdgList_t;

MAE_Ret EmAppCreateSyncInfoView(HWIN hWin, EmAppSyncInfoViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pInputWdg;
    IWidget *pTitleWdg;
}EmAppFmRadioViewWdgList_t;

MAE_Ret EmAppCreateFmRadioView(HWIN hWin, EmAppFmRadioViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pAbsContainerWidget;
}EmAppKeypadViewWdgList_t;

MAE_Ret EmAppCreateKeypadView(HWIN hWin, EmAppKeypadViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pTextWidget;
    IWidget *pHwWidget;
}EmAppTouchPanelViewWdgList_t;

MAE_Ret EmAppCreateTouchPanelView(HWIN hWin, EmAppTouchPanelViewWdgList_t *pWdgList);
MAE_Ret EmAppSetTouchPanelView(HWIN hWin, EmAppTouchPanelViewWdgList_t *pWdgList);

#if defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
MAE_Ret EmAppCreateTouchPanelTestBgView(EmAppData_t *pThis, EmAppTouchPanelEnhanceTest_e eEnhanceTest);
#endif
//*******************************************************************//

typedef struct
{
    IWidget *pOsdWidget;
    IWidget *pTfTextWidget;
    IWidget *pTgTextWidget;
    IWidget *pBit2TextWidget;
    IWidget *pChannelTextWidget;
}EmAppAtvViewWdgList_t;

MAE_Ret EmAppCreateAtvView(HWIN hWin, EmAppAtvViewWdgList_t *pWdgList);
MAE_Ret EmAppSetAtvView(HWIN hWin, EmAppAtvViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
}EmAppWifiTestViewWdgList_t;

MAE_Ret EmAppCreateWifiTestView(HWIN hWin, EmAppWifiTestViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
}EmAppWifiTestSetParamViewWdgList_t;

MAE_Ret EmAppCreateWifiTestSetParamView(HWIN hWin, EmAppWifiTestSetParamViewWdgList_t *pWdgList);
//*******************************************************************//
#ifdef __MULTI_TOUCH__
MAE_Ret EmAppCreateMultiTouchView(HWIN hWin, EmAppMultiTouchWdgList_t *pWdgList);
#endif
//*******************************************************************//
#ifdef __MULTI_TOUCH_SLIM__
MAE_Ret EmAppCreatePinchTestView(HWIN hWin, EmAppPinchTestWdgList_t *pWdgList);
#endif
//*******************************************************************//
#endif //__emapp_view__H
