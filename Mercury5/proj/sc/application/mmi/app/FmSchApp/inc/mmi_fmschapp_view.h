/*****************************************************************************************
* @fmschapp_view.h
*
* Comment:
*
* @author Jack.Kuo@mstarsemi.com
* @       Ryan.Fang@mstarsemi.com
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __fmschapp_view__H
#define __fmschapp_view__H


//*******************************************************************//

MAE_Ret FmSchAppCreatePlayListView(HWIN hWin);

//*******************************************************************//

typedef struct
{
    IWidget *pScrollBarWidget;
    IWidget *pMflContainer;
    IWidget *pTitleDoubleTextWidget;
    IWidget *pTimeTextTimeWidget;
    IWidget *pStatusTextPickWidget;
    IWidget *pFrequencyDoubleTextWidget;
} FmSchAppSetPlayScheduleViewWdgList_t;

MAE_Ret FmSchAppCreateSetPlayScheduleView(HWIN hWin, FmSchAppSetPlayScheduleViewWdgList_t *pWdgList);

//*******************************************************************//

MAE_Ret FmSchAppCreateSelectMenuView(HWIN hWin, MenuWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
    IWidget *pFreqThmTextWdg;
} FmSchAppSelectMyChannelViewWdgList_t;

MAE_Ret FmSchAppCreateSelectMyChannelView(HWIN hWin, FmSchAppSelectMyChannelViewWdgList_t *pWdgList);

//*******************************************************************//

MAE_Ret FmSchAppCreateManualInputView(HWIN hWin, PopUpPromptWdgList_t *pWdgList);

//*******************************************************************//

MAE_Ret FmSchAppCreateSetFrequencyView(HWIN hWin);

//*******************************************************************//

#ifdef __APP_MMI_FM_RADIO_REC__
MAE_Ret FmSchAppCreateRecListView(HWIN hWin);

//*******************************************************************//

typedef struct
{
    IWidget *pScrollBarWidget;
    IWidget *pMflContainer;
    IWidget *pTitleDoubleTextWidget;
    IWidget *pStatusTextPickWidget;
    IWidget *pStartDateTextDateWidget;
    IWidget *pStartTimeTextTimeWidget;
    IWidget *pEndTimeTextTimeWidget;
    IWidget *pFrequencyDoubleTextWidget;
    IWidget *pRecFileDoubleTextWidget;
    IWidget *pRecFileTypePickTextWidget;
    IWidget *pStorageTypePickTextWidget;
} FmSchAppSetRecScheduleViewWdgList_t;

MAE_Ret FmSchAppCreateSetRecScheduleView(HWIN hWin, FmSchAppSetRecScheduleViewWdgList_t *pWdgList);
#endif

MAE_Ret FmSchAppSetInputTextByID(IWidget* pInputWidget, u32 textID);

//*******************************************************************//

#endif //__alarmapp_view__H
