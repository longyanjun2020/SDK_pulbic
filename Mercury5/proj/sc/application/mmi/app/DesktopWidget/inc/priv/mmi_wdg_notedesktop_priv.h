/**
 * @file    mmi_wdg_notedesktop_priv.h
 * @brief   The internal structure of the note desktopwidget

 */

#ifndef __MMI_WDG_NOTEDESKTOP_PRIV_H__
#define __MMI_WDG_NOTEDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_common_util.h"
#include "rs_layout_id.h"

#if defined (__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)

#define NOTE_WIDGET_MAX_ITEM_NUMBER     3

#if defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
#define __ANDROID4_NOTE_DESKTOPWDG__
#endif // __UI_STYLE_MMI_ANDROID_4_0_GADGET__

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	// Subwidget codes
	IWidget			*pIImgWgt[NOTE_WIDGET_MAX_ITEM_NUMBER];
    WPos_t          subWidgetPos[NOTE_WIDGET_MAX_ITEM_NUMBER];
    MAE_ClsId       nSubWidgetClsId[NOTE_WIDGET_MAX_ITEM_NUMBER];
    u32             subWidgetFocusImgId[NOTE_WIDGET_MAX_ITEM_NUMBER];
	IWidget			*pIImgWgt_focus;
	IWidget			*pITextWidget;
    MAEClsId_t      tsPressClsid;
    u8              u8ItemNumber;
    boolean         bShowSubItems;

} NoteDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__
#endif //__MMI_WDG_NOTEDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
