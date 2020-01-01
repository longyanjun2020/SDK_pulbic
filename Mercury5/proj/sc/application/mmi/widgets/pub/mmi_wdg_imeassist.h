/**
* @file    mmi_wdg_imeassist.h
* @brief   This file defines the interface of imeassistwidget.
* 
* @version $Id: mmi_wdg_imeassist.h 7810 2008-03-20 16:42:57Z steve.lee $
*/
#ifndef __MMI_WDG_IMEASSIST_H__
#define __MMI_WDG_IMEASSIST_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgImeAssistWidgetLayoutChange
* @brief      CB register by "PfnWdgImeAssistWidgetLayoutChange"
*             and will be be triggered while ime assist properties changed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nComponentMask    The nth component mask changed
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgImeAssistWidgetLayoutChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nComponentMask, IWidget *pIWidget);

/** WdgImeAssistCreate
* @brief      Create IME Assist widget
*
* @param[out] ppWdgImeAssist      The created ime assist widget will be stored in this pointer
* @param[in]  pOwner              The owner instance
*
* @retval     MAE_RET_SUCCESS     Success
* @retval     others              Failed
*
*/
MAE_Ret WdgImeAssistCreate
(
    IWidget **ppWdgImeAssist,
    IBase   *pOwner
);

/** WdgImeAssistSetDecoratorWidget
* @brief         Set the widget which is decorated by ime assist widget
*
* @param[in]     pWdgImeAssist     The ime assist widget which want to be set
* @param[in]     pChild            The widget which is decorated by ime assist widget.
*
* @retval        None.
*
*/
void WdgImeAssistSetDecoratorWidget
(
    IWidget                 *pWdgImeAssist,
    IWidget                 *pChild
);

/** WdgImeAssistGetObjDecoratorWidget
* @brief         Get the widget which is decorated by ime assist widget
*
* @param[in]     pWdgImeAssist     The ime assist widget which want to be set
* @param[out]    ppChild           The widget which is decorated by ime assist widget.
*
* @retval        None.
*
*/
void WdgImeAssistGetObjDecoratorWidget
(
    IWidget                 *pWdgImeAssist,
    IWidget                 **ppChild
);

/** WdgImeAssistRegisterLayoutChangeCb
* @brief         Register properties change callback; CB will be triggered while imeassist properties changed.
*
* @param[in]     pWdgImeAssist     The ime assist widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgImeAssistRegisterLayoutChangeCb
(
    IWidget                             *pWdgImeAssist,
    PfnWdgImeAssistWidgetLayoutChange   pfn,
    void                                *pUserData
);

/** WdgImeAssistDeregisterLayoutChangeCb
* @brief         Deregister properties change callback.
*
* @param[in]     pWdgImeAssist     The ime assist widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgImeAssistDeregisterLayoutChangeCb
(
    IWidget                             *pWdgImeAssist,
    PfnWdgImeAssistWidgetLayoutChange   pfn,
    void                                *pUserData
);
#endif /* __MMI_WDG_IMEASSIST_H__ */
