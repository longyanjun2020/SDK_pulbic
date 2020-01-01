/**
 * @file    mmi_wdg_commonpickitem_priv.h
 * @version $Id: mmi_wdg_commonpickitem_priv.h 39576 2009-09-07 08:54:00Z steve.lee $
 * @brief   This is the private header file for mmi_wdg_commonpickitem_priv.c
 */
#ifndef MMI_WDG_COMMONPICKITEM_PRIV_H
#define MMI_WDG_COMMONPICKITEM_PRIV_H

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_propcontainerbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
//#define KEEP_WIDGET_PADDING    0xFFFF

///structure for a TextPickItem
typedef struct {
    PropContainerBase_t PCntrBase;
    IWidget         *pItemWidgetTop;
    IWidget         *pPickWidget;
    IWidget         *pItemWidget;
    ModelListener_t MdlListener;
    ModelListener_t PickWdgMdlListener;
} CommonPickItem_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
//new function
MAE_Ret CommonPickItem_New(MAE_ClsId ClsID, void **ppObj);
boolean CommonPickItemWdg_DefHandleEvent(IPropContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret CommonPickItemCnt_Ctor(CommonPickItem_t* pThis);
void    CommonPickItemCnt_Dtor(CommonPickItem_t* pThis);
//container move function
MAE_Ret CommonPickItemCnt_Move(IPropContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isAbove);
//set model function
MAE_Ret CommonPickItemWdg_SetModel(IPropContainer *pIContainer, IModel *pIModel, IBase* pOwner);

#endif //MMI_WDG_COMMONPICKITEM_PRIV_H
/*=============================================================*/
// end of file

