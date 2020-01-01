/**
* @file 	mae_glfotolistwidgetbase.h
* @brief   
*
* @version $Id: mae_glfotolistwidgetbase.h 37664 2010-02-12 09:36:01Z Elvis.Chen $
*/

#ifndef __MAE_GLFOTOLISTWIDGETBASE_H__
#define __MAE_GLFOTOLISTWIDGETBASE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glfotolistwidget_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_menumodel.h"

#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mmi_wdg_common_interface.h"

//mgl
#include "mgl_Scene_Environment.h" 
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
/*=============================================================*/
// type and define
/*=============================================================*/

//typedef u32 (*GLFOTOWDG_RELEASE_FUNC_PTR) (IWidget*);
//typedef void (*GLFOTOLISTWDG_DATACHANGED_PFN)(IWidget *pWdg, u32 nChangedIdx);
typedef void (*GLFOTOLISTWDG_DATACHANGED_PFN)(IWidget *pWdg, GlFotoListDataChangedEvt_t *pInfo);

typedef struct {
	WidgetBaseEx_t			WdgBase;		///< A widgetbase base structure with border
	IMenuModel				*pItemList;		///< A menu model pointer to keep data. 
											///< MenuModelData_t with pItemData in format of GlFotoListWdgData_t
	ModelListener_t			DataMdlLsn;     ///< Model listener for menu model
	u32						nFlags;			///< flags of this widget in bit expression, such as: TS_PRESSED.
	WidgetHandler_t			WdgHdler;
	
	GLFOTOLISTWDG_DATACHANGED_PFN	pfnDataChanged;
	GlFotoListEffect_e		nActiveEffect;
	GlFotoListEffect_e		nInactiveEffect;
	
	/* list properties */
	s32						nFocusIdx;		///< The index of focused element, zero base.
	s32						nFirstDispIdx;	///< The index of first display element, zero base.
	u32						nItemCount;		///< Total size of pItemList
	
	/* item properties */
	u16						nItemWidth;			///< The width of item in pixels
	u16						nItemHeight;		///< The height of item in pixels
	RGBColor_t				nItemBorderColor;	///< border color
	u8						nItemBorderSize;
	
	/* title area */
	MAE_WChar				*pTitleText;
	//MAE_WChar				*pFocusItemText;	///< focus item text, such as filename, item name,....etc; BTW, it cae be retrieved from ItemData
	u32						nEmptyTextID;
	GlFotoListFocusInfo_e	nCheckStyle;	///< check style of this listwdg (reserved)

	/* touch screen */
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv 				*pTouchSrv;	///< Pointer to the touch service object
#endif // __TOUCH_SCREEN_MMI__

	/* MGL part */
	u16						nSceneHandle;	///< MGL scene id
}GlFotoListWdgBase_t;


/* status flag */
enum
{
	GLFOTOLISTBASE_FLAG_START = 0,
	GLFOTOLISTBASE_FLAG_FOCUSFRAM_OF_ITEM = GLFOTOLISTBASE_FLAG_START,	///< 0: not an item widget, 1: being an item widget
	GLFOTOLISTBASE_FLAG_RINGLIST,
	GLFOTOLISTBASE_FLAG_ENABLE_IND_TXT,									///< 0: disabled; 1: enabled; plz refer to PROP_GLFOTOLISTWDG_ENABLE_IND_TXT
	GLFOTOLISTBASE_FLAG_ENABLE_IND_TXT_TOTAL,							///< 0: disabled; 1: enabled; plz refer to PROP_GLFOTOLISTWDG_ENABLE_IND_TXT_TOTAL
	GLFOTOLISTBASE_FLAG_ENABLE_MIRROR,									///< 0: disabled; 1: enabled; plz refer to PROP_GLFOTOLISTWDG_ENABLE_MIRROR
#ifdef __TOUCH_SCREEN_MMI__
	GLFOTOLISTBASE_FLAG_IS_TOUCH_PRESSED,                      			///< 0: Touch pressed now; 1: Touch not pressed
#endif // __TOUCH_SCREEN_MMI__
	GLFOTOLISTBASE_FLAG_END
};

#define GLFOTOLISTBASE_MASK_BITSHIFT(_f)	(_f)
#define GLFOTOLISTBASE_MASK_FLAG(_f)		(1<<GLFOTOLISTBASE_MASK_BITSHIFT(_f))

#define GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, _f) \
	(((_pGlFotoListBase)->nFlags&GLFOTOLISTBASE_MASK_FLAG(_f))>>GLFOTOLISTBASE_MASK_BITSHIFT(_f))
#define GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, _f) \
	(_pGlFotoListBase)->nFlags = ((_pGlFotoListBase)->nFlags&(~GLFOTOLISTBASE_MASK_FLAG(_f)))|(((u32)_b)<<GLFOTOLISTBASE_MASK_BITSHIFT(_f))

// macro to get flag
#define GLFOTOLISTBASE_IS_FOCUSFRAM_ENABLED(_pGlFotoListBase) \
	(boolean)GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, GLFOTOLISTBASE_FLAG_START)
#define GLFOTOLISTBASE_IS_RINGLIST(_pGlFotoListBase) \
	(boolean)GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, GLFOTOLISTBASE_FLAG_RINGLIST)
#define GLFOTOLISTBASE_IS_IND_TXT_ENABLED(_pGlFotoListBase) \
	(boolean)GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, GLFOTOLISTBASE_FLAG_ENABLE_IND_TXT)
#define GLFOTOLISTBASE_IS_IND_TXT_TOTAL_ENABLED(_pGlFotoListBase) \
	(boolean)GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, GLFOTOLISTBASE_FLAG_ENABLE_IND_TXT_TOTAL)
#define GLFOTOLISTBASE_IS_MIRROR_ENABLED(_pGlFotoListBase) \
	(boolean)GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, GLFOTOLISTBASE_FLAG_ENABLE_MIRROR)
		
#ifdef __TOUCH_SCREEN_MMI__
#define GLFOTOLISTBASE_IS_TOUCH_PRESSED(_pGlFotoListBase) \
	(boolean)GLFOTOLISTBASE_GET_FLAG(_pGlFotoListBase, GLFOTOLISTBASE_FLAG_IS_TOUCH_PRESSED)
#endif

// macro to set flag
#define GLFOTOLISTBASE_SET_FOCUSFRAM_ENABLED(_pGlFotoListBase, _b) \
	GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, GLFOTOLISTBASE_FLAG_FOCUSFRAM_OF_ITEM)
#define GLFOTOLISTBASE_SET_RINGLIST(_pGlFotoListBase, _b) \
	GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, GLFOTOLISTBASE_FLAG_RINGLIST)
#define GLFOTOLISTBASE_SET_IND_TXT_ENABLED(_pGlFotoListBase, _b) \
	GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, GLFOTOLISTBASE_FLAG_ENABLE_IND_TXT)
#define GLFOTOLISTBASE_SET_IND_TXT_TOTAL_ENABLED(_pGlFotoListBase, _b) \
	GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, GLFOTOLISTBASE_FLAG_ENABLE_IND_TXT_TOTAL)
#define GLFOTOLISTBASE_SET_MIRROR_ENABLED(_pGlFotoListBase, _b) \
	GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, GLFOTOLISTBASE_FLAG_ENABLE_MIRROR)

#ifdef __TOUCH_SCREEN_MMI__
#define GLFOTOLISTBASE_SET_TOUCH_PRESSED(_pGlFotoListBase, _b) \
	GLFOTOLISTBASE_SET_FLAG(_pGlFotoListBase, _b, GLFOTOLISTBASE_FLAG_IS_TOUCH_PRESSED)
#endif

/*=============================================================*/
// functions
/*=============================================================*/
/*------------------------------------------------
* New function, Constructor and Destructor
--------------------------------------------------*/
MAE_Ret GlFotoListWdgBase_Ctor(GlFotoListWdgBase_t		*pThis,
							   WDG_DRAW_FUNC_PTR		pfnDraw,
							   GLFOTOLISTWDG_DATACHANGED_PFN	pfnDataChanged);
void GlFotoListWdgBase_Dtor(GlFotoListWdgBase_t *pThis);

/* viewmodel notify */
void GlFotoListWdgBase_NotifyFocusChange(GlFotoListWdgBase_t *pThis, s32 nPrevFocusIdx);
void GlFotoListWdgBase_NotifyFocusSelect(GlFotoListWdgBase_t *pThis);
void GlFotoListWdgBase_NotifyViewMdlWithHistoryInfo(GlFotoListWdgBase_t *pThis, u32 nEvtId);
boolean GlFotoListWdgBase_DefHandleEvent(IWidget *pWdg, MAE_EventId nEvtId, u32 P1, u32 P2);

// a general case to notify viewmodel
void GlFotoListWdgBase_ViewMdlNotify(GlFotoListWdgBase_t *pThis, u32 nEvtId, u32 Param);

#endif //__MAE_GLFOTOLISTWIDGETBASE_H__
