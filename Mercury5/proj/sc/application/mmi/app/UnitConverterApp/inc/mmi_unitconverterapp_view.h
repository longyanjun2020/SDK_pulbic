/*****************************************************************************************
* @unitconverterapp_view.h
*
* Comment: 
*
* @version:0.0.2  @ 2009.12.01 
*****************************************************************************************/
#ifndef __unitconverterapp_view__H
#define __unitconverterapp_view__H


typedef struct
{
    IWidget *pWdgContainer;
    IWidget *pWdgType;
    IWidget *pWdgType1;
    IWidget *pWdgSolarText;
    IWidget *pWdgInput1;
    IWidget *pWdgSolarInput;
    IWidget *pWdgType2;
    IWidget *pWdgLunarText;
    IWidget *pWdgInput2;
    IWidget *pWdgLunarInput;
    IWidget *pWdgRate;
    IWidget *pWdgLeapMonth;
} UnitConverterMainViewWdgList_t;

MAE_Ret UnitConverterCreateMainView(HWIN hWin, UnitConverterMainViewWdgList_t *pWdgList);
MAE_Ret UnitConverterSetMainView(UnitConverterAppData_t* pThis);

//*******************************************************************//

typedef struct
{
    IWidget *pPropContainer;
    IWidget *pWdgEditInput;
}UnitConverterEditViewWdgList_t;

MAE_Ret UnitConverterCreateEditView(HWIN hWin, UnitConverterEditViewWdgList_t *pWdgList);
MAE_Ret UnitConverterSetEditView(UnitConverterAppData_t* pThis);
//*******************************************************************//

typedef struct
{
    IWidget *pWdgBaseCurrency;
    IWidget *pWdgRateInput;
    IWidget *pWdgTargetCurrency;
    IWidget *pWdgRateRange;
} UnitConverterRateViewWdgList_t;

MAE_Ret UnitConverterCreateRateView(HWIN hWin, UnitConverterRateViewWdgList_t *pWdgList);
MAE_Ret UnitConverterSetRateView(UnitConverterAppData_t* pThis);


#endif //__unitconverterapp_view__H
