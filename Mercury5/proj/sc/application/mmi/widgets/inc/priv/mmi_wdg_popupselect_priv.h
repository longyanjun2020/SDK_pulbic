#ifndef __MMI_WDG_POPUPSELECT_PRIV_H__
#define __MMI_WDG_POPUPSELECT_PRIV_H__ 

#include "mmi_mae_common_def.h"
#include "mmi_wdg_popupselect.h"
#include "mae_abscontainerbase.h"
#include "img_data.h"
#include "mmi_wdg_menu.h"
#include "mmi_mae_menumodel.h"
#include "mmi_mae_softkeymodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef struct
{
    AbsContainerBase_t ACntrBase;
    ISoftkeyModel *pISoftkeyMdl;
    IWidget *pIOptMenuWdg;
    ModelListener_t ViewMdlListener;
	s32 sPosX;
	s32 sMenuOffsetY;
    boolean            bTitleEnable;
    ItemDisplayStyle_t u8ItemStyle;
} _MAE_PopupSelectWidget;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret PopupSelectWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean PopupSelectWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret PopupSelectWidgetConstructor(_MAE_PopupSelectWidget *pThis);
static void PopupSelectWidget_Dstor(_MAE_PopupSelectWidget *pThis);

static MAE_Ret PopupSelectWidget_SetModel(IAbsContainer *pIAbsContainer, IModel *pIModel, IBase* pOwner);

static MAE_Ret PopupSelectWidget_Init(IAbsContainer * pIAbsContainer);
static void _PopupSelectWidget_UpdateModel(_MAE_PopupSelectWidget *pThis);

static void _PopupSelectWidget_MenuSizeChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);

#endif /* __MMI_WDG_POPUPSELECT_PRIV_H__ */
