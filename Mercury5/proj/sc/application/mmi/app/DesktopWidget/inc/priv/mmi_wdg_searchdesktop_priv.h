/**
 * @file    mmi_wdg_searchdesktop_priv.h
 * @brief   The internal structure of the search desktopwidget

 */

#ifndef __MMI_WDG_SEARCHDESKTOP_PRIV_H__
#define __MMI_WDG_SEARCHDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_srv_header.h"
#include "rs_layout_id.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) 

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	IWidget			*pITitleWidget;

#if !defined(__3D_UI_IDLE_MULTIPAGE__) 
	// Subwidget codes
	IWidget			*pIInputMethodImgWidget;
	IWidget			*pIInputWidget;
	IWidget			*pISearchBtnWidget;
	IWidget			*pIImeAssistWidget;

	ModelListener_t tInputViewMdlListener;

	boolean			bIsLongPressed;			// For skip click event after long press
	boolean			bTouchInSubwidget;
	u16				uSubwidgetIndex;
#endif
} SearchDesktopWdg_t;

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
#if !defined(__3D_UI_IDLE_MULTIPAGE__) 
void SearchDesktopWidgetFreeButtonDataModel(void *pUserData, IBase *pOwner);
#endif

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__

#endif //__MMI_WDG_SEARCHDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
