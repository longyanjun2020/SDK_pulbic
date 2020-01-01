/**
 * @file    mmi_wdg_doubleitem_priv.h
 * @version $Id: mmi_wdg_doubleitem_priv.h 39576 2009-09-07 08:54:00Z steve.lee $
 * @brief   This is the private header file for mmi_wdg_doubleitem.h
 */
#ifndef __MMI_WDG_DOUBLEITEM_PRIV_H__
#define __MMI_WDG_DOUBLEITEM_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_abscontainerbase.h"
#include "mmi_wdg_text.h"
#include "mmi_layout.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/**
* Flags in MenuWidget_t
*/
enum
{
	DOUBLEITEM_FLAG_START = 0,
	DOUBLEITEM_FLAG_DISABLE_LINE2_TEXT_BG = DOUBLEITEM_FLAG_START,	///< Default: FALSE
	DOUBLEITEM_FLAG_DISABLE_UP_WIDGET_ANIM,						///< To disable upper widget animation
	DOUBLEITEM_FLAG_DISABLE_DOWN_WIDGET_ANIM, 					///< To disable down widget animation
	DOUBLEITEM_FLAG_END
};	

/**
* Flag Mask
*/
#define DOUBLEITEM_MASK_DISABLE_LINE2_TEXT_BG		(1<<DOUBLEITEM_FLAG_DISABLE_LINE2_TEXT_BG)
#define DOUBLEITEM_MASK_DISABLE_UP_WIDGET_ANIM		(1<<DOUBLEITEM_FLAG_DISABLE_UP_WIDGET_ANIM)
#define DOUBLEITEM_MASK_DISABLE_DOWN_WIDGET_ANIM	(1<<DOUBLEITEM_FLAG_DISABLE_DOWN_WIDGET_ANIM)

/**
* Macro to get flag value
*/
#define DOUBLEITEM_IS_DISABLE_LINE2_TEXT_BG(_pDoubleItemWdg) \
	(boolean)(((_pDoubleItemWdg)->nFlags&DOUBLEITEM_MASK_DISABLE_LINE2_TEXT_BG)>>DOUBLEITEM_FLAG_DISABLE_LINE2_TEXT_BG)
#define DOUBLEITEM_IS_DISABLE_UP_WIDGET_ANIM(_pDoubleItemWdg) \
	(boolean)(((_pDoubleItemWdg)->nFlags&DOUBLEITEM_MASK_DISABLE_LINE2_TEXT_BG)>>DOUBLEITEM_FLAG_DISABLE_UP_WIDGET_ANIM)
#define DOUBLEITEM_IS_DISABLE_DOWN_WIDGET_ANIM(_pDoubleItemWdg) \
	(boolean)(((_pDoubleItemWdg)->nFlags&DOUBLEITEM_MASK_DISABLE_DOWN_WIDGET_ANIM)>>DOUBLEITEM_FLAG_DISABLE_DOWN_WIDGET_ANIM)

/**
* Macro to Set flag value
*/
#define DOUBLEITEM_SET_DISABLE_LINE2_TEXT_BG(_pDoubleItemWdg, _b) \
	(_pDoubleItemWdg)->nFlags = ((_pDoubleItemWdg)->nFlags&(~DOUBLEITEM_MASK_DISABLE_LINE2_TEXT_BG))|(((u32)_b)<<DOUBLEITEM_FLAG_DISABLE_LINE2_TEXT_BG)
#define DOUBLEITEM_SET_DISABLE_UP_WIDGET_ANIM(_pDoubleItemWdg, _b) \
	(_pDoubleItemWdg)->nFlags = ((_pDoubleItemWdg)->nFlags&(~DOUBLEITEM_MASK_DISABLE_LINE2_TEXT_BG))|(((u32)_b)<<DOUBLEITEM_FLAG_DISABLE_UP_WIDGET_ANIM)
#define DOUBLEITEM_SET_DISABLE_DOWN_WIDGET_ANIM(_pDoubleItemWdg, _b) \
	(_pDoubleItemWdg)->nFlags = ((_pDoubleItemWdg)->nFlags&(~DOUBLEITEM_MASK_DISABLE_DOWN_WIDGET_ANIM))|(((u32)_b)<<DOUBLEITEM_FLAG_DISABLE_DOWN_WIDGET_ANIM)


///structure for a 
typedef struct {
	AbsContainerBase_t	AbsCntrBase;			///< Using AbsContainer_t as base structure.
	ModelListener_t	MdlListener;

    IWidget			*pUpperWidget;	
	IWidget			*pDownWidget;

	MAE_IId			nUpperWidgetMdlId;      ///> the interface id of upper widget's model
	MAE_IId			nDownWidgetMdlId;       ///> the interface id of down widget's model
	
	u32				nFlags;
	ModelListener_t	tTextMdlListener;		// for CLSID_TEXT_LINE2INFO_WIDGET Line2 text model
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload

} DoubleItemWidget_t;

// RELOAD flag
enum
{
	DOUBLEITEM_WDG_RELOAD_FLAG_START = 0,
	DOUBLEITEM_WDG_RELOAD_FLAG_TEXTCOLOR = DOUBLEITEM_WDG_RELOAD_FLAG_START,   ///< tTextColor
	DOUBLEITEM_WDG_RELOAD_FLAG_HIGHLIGHTTEXTCOLOR,	///< tHighlightTextColor
	DOUBLEITEM_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define DOUBLEITEM_WDG_RELOAD_MASK_TEXTCOLOR        (1<<DOUBLEITEM_WDG_RELOAD_FLAG_TEXTCOLOR)
#define DOUBLEITEM_WDG_RELOAD_MASK_HIGHLIGHTTEXTCOLOR         (1<<DOUBLEITEM_WDG_RELOAD_FLAG_HIGHLIGHTTEXTCOLOR)
/**
* Macro to get flag value
*/
#define DOUBLEITEM_WDG_TEXTCOLOR_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&DOUBLEITEM_WDG_RELOAD_MASK_TEXTCOLOR)>>DOUBLEITEM_WDG_RELOAD_FLAG_TEXTCOLOR)
#define DOUBLEITEM_WDG_HIGHLIGHTTEXTCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&DOUBLEITEM_WDG_RELOAD_MASK_HIGHLIGHTTEXTCOLOR)>>DOUBLEITEM_WDG_RELOAD_FLAG_HIGHLIGHTTEXTCOLOR)
/**
* Macro to Set flag value
*/
#define DOUBLEITEM_WDG_TEXTCOLOR_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~DOUBLEITEM_WDG_RELOAD_MASK_TEXTCOLOR))|(((u32)_b)<<DOUBLEITEM_WDG_RELOAD_FLAG_TEXTCOLOR)
#define DOUBLEITEM_WDG_HIGHLIGHTTEXTCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~DOUBLEITEM_WDG_RELOAD_MASK_HIGHLIGHTTEXTCOLOR))|(((u32)_b)<<DOUBLEITEM_WDG_RELOAD_FLAG_HIGHLIGHTTEXTCOLOR)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret DoubleItem_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean DoubleItemWdg_DefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret DoubleItemCnt_Ctor(DoubleItemWidget_t *pThis, MAE_ClsId ClsID);
void DoubleItemCnt_Dtor(DoubleItemWidget_t * pThis);

//release function
u32 DoubleItemCnt_Release(IAbsContainer *pIAbsContainer);

//setsize function
void DoubleItemCnt_SetSize(IAbsContainer *pIAbsContainer, WidgetSize_t *pSize);

//container move function
MAE_Ret DoubleItemCnt_Move(IAbsContainer *pIAbsContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isAbove);

//set model function
MAE_Ret DoubleItemWdg_SetModel(IAbsContainer *pIAbsContainer, IModel *pIModel, IBase* pOwner);

//other functions for IWidget interface are used in container base
boolean DoubleItemWdg_DefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

static void _DoubleItemWidget_ReloadRC(DoubleItemWidget_t *pThis, DisplayMode_e nDispMode);

#endif //__MMI_WDG_DOUBLEITEM_PRIV_H__
/*=============================================================*/
// end of file

