/**
 * @file mmi_wdg_inputgrid_priv.h
 * @brief This file defines the data structure of menu widget and function prototype for implementation.
 *
 * @version $Id: mmi_wdg_inputgrid_priv.h 36049 2009-07-20 03:25:56Z william.lien $
 */
#ifndef __MMI_WDG_INPUTGRID_PRIV_H__
#define __MMI_WDG_INPUTGRID_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_decoratorbase.h"
#include "mmi_mae_menumodel.h"
#include "mmi_wdg_menu.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	DecoratorEx_t			DecBase;
	IWidget             *pIMenuWidget;
	IMenuModel          *pIMenuModel;
    u16                 nCol;
	u16                 nRow;
    FontInfo            fontInfo;
} InputGridWidget_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret InputGridWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean InputGridWidget_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgInputGridConstructor(InputGridWidget_t *pThis);
void _WdgInputGridDestructor(InputGridWidget_t *pThis);

void InputGridWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
void InputGridWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
void InputGridWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
MAE_Ret InputGridWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
boolean InputGridWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
MAE_Ret InputGridWidget_GetViewModel(IDecorator *pIWidget, IModel **ppObj, IBase *pOwner);
MAE_Ret InputGridWidget_GetModel(IDecorator* pIDecorator, MAE_IId iId, IModel** ppObj, IBase* pOwner);
boolean InputGridWidget_HandleKeyEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);
void InputGridWidget_MenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pMenuWdg);
void _WdgInputGridReloadRC(InputGridWidget_t *pThis);
#endif //__MMI_WDG_INPUTGRID_PRIV_H__
/*=============================================================*/
// end of file
