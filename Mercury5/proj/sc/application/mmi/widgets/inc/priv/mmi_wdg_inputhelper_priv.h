/**
 * @file mmi_wdg_inputhelper_priv.h
 * @brief This file defines the data structure of helper widget and function prototype for implementation.
 *
 * @version $Id: mmi_wdg_inputhelper_priv.h 24391 2009-03-02 07:00:51Z william.lien $
 */
#ifndef __MMI_WDG_INPUTHELPER_PRIV_H__
#define __MMI_WDG_INPUTHELPER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_decoratorbase.h"
#include "mmi_mae_textmodel.h"
#include "mmi_mae_softkeymodel.h"
/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	DecoratorEx_t	DecBase;
	IWidget	*pITitleWidget;
	IWidget *pIInputWidget;
	IWidget *pIScrollbarWidget;
	ITextModel *pITextModel;
	ISoftkeyModel *pISoftkeyModel;
	//ModelListener_t	ThemeMdlLsn;
	boolean bMyWord;
  } InputHelperWidget_t;



#define INPUTHELPERIDGET_DEFAULT_BGCOLOR (MAKE_RGB(186,213,234))			// default bg color for help widget
#define INPUTHELPERIDGET_DEFAULT_PADDINGSIZE			2		//default padding size
/*------------------------------------------------------------------------------------------
* New function and Event handler
------------------------------------------------------------------------------------------*/
__SLDPM_FREE__ MAE_Ret InputHelperWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean InputHelperWidget_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);
/*------------------------------------------------------------------------------------------
* Non-interface functions
------------------------------------------------------------------------------------------*/
__SLDPM_FREE__ MAE_Ret _WdgInputHelperConstructor(InputHelperWidget_t *pThis);
void _WdgInputHelperDestructor(InputHelperWidget_t *pThis);

boolean InputHelperWidget_HandleKeyEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);
void InputHelperWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
void InputHelperWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
void InputHelperWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
MAE_Ret InputHelperWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
MAE_Ret InputHelperWidget_GetViewModel(IDecorator *pIWidget, IModel **ppObj, IBase *pOwner);
MAE_Ret InputHelperWidget_GetModel(IDecorator* pIDecorator, MAE_IId iId, IModel** ppObj, IBase* pOwner);
static void InputHelperWidget_NoifyInputComplete(IDecorator* pIDecorator);
static void InputHelperWidget_LoadResource(IDecorator* pIDecorator);

#endif //__MMI_WDG_INPUTHELPER_PRIV_H__
/*=============================================================*/
// end of file
