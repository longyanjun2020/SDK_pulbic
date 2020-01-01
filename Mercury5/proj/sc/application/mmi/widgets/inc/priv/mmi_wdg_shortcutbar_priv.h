/**
 * @file	mmi_wdg_shortcutbar_priv.h
 * @version	$Id: mmi_wdg_shortcutbar_priv.h 41085 2009-09-22 15:14:03Z ryan.chou $
 * @brief
 *
 */
#ifndef __MMI_WDG_SHORTCUTBAR_PRIV_H__
#define __MMI_WDG_SHORTCUTBAR_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_abscontainerbase.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_cfgsrv.h"
#include "mae_animation.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define SHORTCUTBARWDG_ANIMATION_TIMER_DLEAY		20

typedef enum
{
	BITMAP_SHORTCUTBAR_FIRST,
	BITMAP_SHORTCUTBAR_SWITCH_OFF = BITMAP_SHORTCUTBAR_FIRST,
	BITMAP_SHORTCUTBAR_SWITCH_OFF_PRESS,
	BITMAP_SHORTCUTBAR_SWITCH_ON,
    BITMAP_SHORTCUTBAR_SWITCH_ON_PRESS,
	BITMAP_SHORTCUTBAR_LAST = BITMAP_SHORTCUTBAR_SWITCH_ON_PRESS
} SHORTCUTBAR_BITMAP_ELEMENT_e;

typedef struct {

	AbsContainerBase_t	AbsCntrBase;				///< Using AbsContainer_t as base structure.
	IWidget			*pShortcutWdg;			    ///< An Proportion container to be input shortcut items
	IWidget		*pViewPortWdg;
	WidgetHandler_t ViewPortWdgHdler;   /// event Handler to process shortcut listwidget TS events
	IVectorModel	*pShortcutWdgVctMdl;
	u8 u8FocusWdgIdx;
	ICFGSrv         *pICFGSrv;    //for get and set configuration items.
	u8					nAnimationDelPhase;
	u8					nAnimationAddPhase;
	IWidget		*pEmptyItemWdg;
	IWidget		*pAddinItemWdg;
	u16				u16AddinDefaultHeight;
	IWidget		*pOpTextWdg[2];
	boolean			bTSPressed;
    boolean			bResLoaded;
#if defined(__3D_UI_IDLE_GADGETBAR__)
    IAnimation  *pAnimation;
    Shortcutbar_Icon_Anim_e eIconAnim;
#endif //#if defined(__3D_UI_IDLE_GADGETBAR__)
} _ShortcutBarWidget_t;

typedef struct{
	u8 u8ItemId;
	IWidget *pItemWdg;
} _WdgItemData_t;
/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret ShortcutBarWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean ShortcutBarWdg_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgShortcutBarConstructor(_ShortcutBarWidget_t *pThis );
void _WdgShortcutBarDestructor(_ShortcutBarWidget_t *pThis);
static void _ShortcutBarWidget_ReloadRC(_ShortcutBarWidget_t *pThis, DisplayMode_e nDispMode);

#endif //__MMI_WDG_SHORTCUTBAR_PRIV_H__
/*=============================================================*/
// end of file













