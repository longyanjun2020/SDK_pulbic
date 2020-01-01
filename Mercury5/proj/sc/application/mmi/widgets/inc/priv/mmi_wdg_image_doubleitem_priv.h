/**
 * @file    mmi_wdg_image_doubleitem_priv.h
 * @version $Id: mmi_wdg_image_doubleitem_priv.h 14596 2008-10-01 09:04:35Z paul.ouyang $
 * @brief   This file defines the interface of IIMAGEDOUBLEITEMWIDGET
 * @layout
 *  ------------------------------------------
 *  |  ----  ------------------------------- |
 *  | |    | |UpperItem                    | |
 *  | |IMG | ------------------------------- |
 *  | |    | |DownItem                     | |
 *  |  ----  ------------------------------- |
 *  ------------------------------------------
 */

#ifndef __MMI_WDG_IMAGE_DOUBLEITEM_PRIV_H__
#define __MMI_WDG_IMAGE_DOUBLEITEM_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"    
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_shell.h"
#include "mae_propcontainerbase.h"

#include "mmi_wdg_text.h"
#include "mmi_wdg_layout.h"


/**
 * Support class id:1.CLSID_IMAGE_DOUBLE_TEXT_WIDGET
 *					2.CLSID_IMAGE_TITEXT_WIDGET
 *                  3.CLSID_IMAGE_TITI_WIDGET
 *					
 *					
 *					
 *
 *
 *  CLSID_IMAGE_DOUBLE_TEXT_WIDGET:
 *  ------------------------------------------
 *  |  ----  ------------------------------- |
 *  | |    | |Text	                       | |
 *  | |IMG | ------------------------------- |
 *  | |    | |Text                         | |
 *  |  ----  ------------------------------- |
 *  ------------------------------------------
 *
 *
 *  CLSID_IMAGE_TITEXT_WIDGET
 *  ------------------------------------------
 *  |  ----  ------------------------------- |
 *  | |    | |Text	                   |IMG| |
 *  | |IMG | ------------------------------- |
 *  | |    | |Text                         | |
 *  |  ----  ------------------------------- |
 *  ------------------------------------------
 *
 *   
 *
 */

/*=============================================================*/
// type and define
/*=============================================================*/

///structure for a 
typedef struct {
    PropContainerBase_t PCntrBase;
    
	IWidget		*pPreImageWidget;	
    IWidget		*pPostUpperWidget;	
	IWidget		*pPostDownWidget;

	MAE_IId		nPreImageWidgetMdlId;       ///> the interface id of down widget's model
	MAE_IId		nPostUpperWidgetMdlId;      ///> the interface id of upper widget's model
	MAE_IId		nPostDownWidgetMdlId;       ///> the interface id of down widget's model
     
	ModelListener_t    MdlListener;
} WdgImageDoubleItem_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret Image_DoubleItem_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgImageDoubleItemDefHandleEvent(IContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgImageDoubleItemConstructor(WdgImageDoubleItem_t* pThis);

void _WdgImageDoubleItemDestructor(WdgImageDoubleItem_t* pThis);

//container move function
MAE_Ret _WdgImageDoubleItemCntMove(IPropContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isAbove);

//set model function
MAE_Ret _WdgImageDoubleItemSetModel(IPropContainer *pIContainer, IModel *pIModel, IBase* pOwner);


#endif //__MMI_WDG_IMAGE_DOUBLEITEM_PRIV_H__
/*=============================================================*/
// end of file
