/**
* @file    mmi_wdg_image_doubleitem_multifield.h
* @version $Id: mmi_wdg_image_doubleitem_multifield.h added
* @brief   This is the private header file for mmi_wdg_image_doubleitem_multifield.h
*/
#ifndef __MMI_WDG_IMAGE_DOUBLEITEM_MULTIFIELD_PRIV_H__
#define __MMI_WDG_IMAGE_DOUBLEITEM_MULTIFIELD_PRIV_H__
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
/*=============================================================*/
// type and define
/*=============================================================*/
///structure for a
typedef struct {
	PropContainerBase_t	PCntrBase;

	IWidget *pItemPreWdg;
	IWidget *pItemBackUpWdg;
    IWidget *pItemBackDownFirstWdg;
    IWidget *pItemBackDownSecWdg;
    IWidget *pItemBackDownThirdWdg;
    IWidget *pItemBackDownFourthWdg;

	MAE_IId		nPreWdgMdlId;      ///> the interface id of upper widget's model
	MAE_IId     nBackUpWdgMdlId;
    MAE_IId     nBackDownFirstWdgMdlId;
	MAE_IId		nBackDownSecWdgMdlId;       ///> the interface id of down widget's model
	MAE_IId     nBackDownThirdWdgMdId;
    MAE_IId     nBackDownFourthWdgMdId;

	ModelListener_t    MdlListener;
} ImageDoubleItemMultiFieldWidget_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/

//new function
MAE_Ret ImageDoubleItemMultiFieldWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret ImageDoubleItemMultiFieldWdg_Ctor(ImageDoubleItemMultiFieldWidget_t* pThis, MAE_ClsId ClsID);
void ImageDoubleItemMultiFieldWdg_Dtor(ImageDoubleItemMultiFieldWidget_t* pThis);


/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/

//set model function
MAE_Ret ImageDoubleItemMultiFieldWdg_SetModel(IPropContainer *pIContainer, IModel *pIModel, IBase* pOwner);

//Get preferred size function => use the function in PropContainer

//other functions for IWidget interface are used in container base
boolean ImageDoubleItemMultiFieldWdg_DefHandleEvent(IPropContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// end of file
#endif //__MMI_WDG_IMAGE_DOUBLEITEM_MULTIFIELD_PRIV_H__

