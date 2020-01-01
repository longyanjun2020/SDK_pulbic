/**
* @file 	mmi_wdg_mflcontainer_priv.h
* @brief   Multi-Field List Container
*
* @version $Id: mmi_wdg_mflcontainer_priv.h 25372 2009-03-11 08:10:22Z mark.yang $
*/
#ifndef __MMI_WDG_MFLCONTAINER_PRIV_H__
#define __MMI_WDG_MFLCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_mflcontainer.h"
#include "mae_containerbase.h"
#include "mae_wdgbackground.h"


/*=============================================================*/
// type and define
/*=============================================================*/
#ifdef __TOUCH_SCREEN_MMI__
enum {
	MFL_SLIDE_TO_NONE = 0,
	MFL_SLIDE_TO_TOP,      ///< minus y offset
	MFL_SLIDE_TO_BOTTOM,   ///< plus y offset
	MFL_SLIDE_ROLLBACK_Y,
	MFL_SLIDE_END
};
typedef u8 MFLSildeMode_t;
#endif // __TOUCH_SCREEN_MMI__

typedef struct {
	ContainerBase_t     CntrBase;           ///< Use this as a base structure.
	u32					nFlags;
	s32                 nHighlightIdx;      ///< A zero-base index to keep focused/highlight index.
	s32                 nOffsetY;			///< y coordinate offset for layout, base on the content rectangle of MFL container.(usually minus)
	//ModelListener_t     ThemeMdlLsn;        ///< A theme model listener
	WdgItemBG_t         ItemBg;             ///< Background color/image of focused item.
	u16                 nItemHeight;        ///< The height of every item in pixel
	u16                 nSelItemSize;       ///< The height of focused item in pixel. Using nItemHeight if zero.
	u16                 nRowGap;            ///< Row gap in pixel between every item.
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;
	s32					nPressIdx;      /// < The focus index when touch is pressed>
	u32					nSlideOffset;
	s32					nTS_StartY;
	u32					nTS_StartOffsetY;
	MFLSildeMode_t SlideMode;
#endif //__TOUCH_SCREEN_MMI__

	/// followings are status flags
#ifdef __TOUCH_SCREEN_MMI__
	u32                 bIsTouchPressed : 1; ///< a flag to indicate if this mfl is touch pressed
	u32                 bHlChangedByTouch : 1; ///< a flag to indicate if highlight index is changed by touch
	u32                 bPassTsEvtToHlItem : 1;
	u32                 bSlideChecking : 1;
	u32                 bEnableTouchSliding : 1;
	u32                 bSlideTimerRunning : 1;
#endif //__TOUCH_SCREEN_MMI__
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
} MFLContainer_t;


/**
* @brief	structure of widget cell used in MFL-contianer
*/
typedef struct {
	WidgetCell_t    WCellBase;
	u16				id;
} MFLWidgetCell_t;

/**
* @brief	Structure for MFL container view model event EVT_VIEWMDL_MFL_FOCUS_CHANGE, EVT_VIEWMDL_MFL_FOCUS_SELECT
*/
typedef struct {
	ModelEvent_t 	MEvtBase;
	MFLFocusData_t	stMFLFcsData;
} MFLViewMdlEvent_t;


/**
* @brief Default selected item background color
*/
#define MFL_DEFAULT_SELECTITEM_COLOR (MAKE_RGB(128,128,0))

/*
/// Flags
enum
{
	MFLCNTNR_FLAG_START = CNTNR_BASE_FLAG_END,
#ifdef __TOUCH_SCREEN_MMI__
	MFLCNTNR_FLAG_TOUCH_PRESSED = MFLCNTNR_FLAG_START,
	MFLCNTNR_FLAG_HL_CHANGED_BY_TOUCH,
#endif //__TOUCH_SCREEN_MMI__
	MFLCNTNR_BASE_FLAG_END
};
*/

#ifdef __TOUCH_SCREEN_MMI__
/*
/// Mask
#define MFLCNTNR_MASK_TOUCH_PRESSED         (1<<MFLCNTNR_FLAG_TOUCH_PRESSED)          ///< Touch pressed or not
#define MFLCNTNR_MASK_HL_CHANGED_BY_TOUCH   (1<<MFLCNTNR_FLAG_HL_CHANGED_BY_TOUCH)    ///< is Highlight changed by touch.
*/
/// Macro to get flags data
#define MFLCNTNR_IS_TOUCH_PRESSED(_pMflCntr) \
	(_pMflCntr)->bIsTouchPressed
	//(boolean)(((_pMflCntr)->CntrBase.WdgBase.Flags&MFLCNTNR_MASK_TOUCH_PRESSED)>>MFLCNTNR_FLAG_TOUCH_PRESSED)

#define MFLCNTNR_IS_HL_CHANGED_BY_TOUCH(_pMflCntr) \
	(_pMflCntr)->bHlChangedByTouch
	//(boolean)(((_pMflCntr)->CntrBase.WdgBase.Flags&MFLCNTNR_MASK_HL_CHANGED_BY_TOUCH)>>MFLCNTNR_FLAG_HL_CHANGED_BY_TOUCH)

/// Macro to set flags data
#define MFLCNTNR_SET_TOUCH_PRESSED(_pMflCntr, _b) \
	(_pMflCntr)->bIsTouchPressed = (_b)
	//(_pMflCntr)->CntrBase.WdgBase.Flags = ((_pMflCntr)->CntrBase.WdgBase.Flags&(~MFLCNTNR_MASK_TOUCH_PRESSED))|(((u32)_b)<<MFLCNTNR_FLAG_TOUCH_PRESSED)

#define MFLCNTNR_SET_HL_CHANGED_BY_TOUCH(_pMflCntr, _b) \
	(_pMflCntr)->bHlChangedByTouch = (_b)
	//(_pMflCntr)->CntrBase.WdgBase.Flags = ((_pMflCntr)->CntrBase.WdgBase.Flags&(~MFLCNTNR_MASK_HL_CHANGED_BY_TOUCH))|(((u32)_b)<<MFLCNTNR_FLAG_HL_CHANGED_BY_TOUCH)

#endif //__TOUCH_SCREEN_MMI__

// RELOAD flag
enum
{
	MFLCONTAINER_RELOAD_FLAG_START = 0,
	MFLCONTAINER_RELOAD_FLAG_OFFSETY = MFLCONTAINER_RELOAD_FLAG_START,   ///< nOffsetY
	MFLCONTAINER_RELOAD_FLAG_ITEMHEIGHT,	///< nItemHeight
	MFLCONTAINER_RELOAD_FLAG_SELITEMSIZE,	///< nSelItemSize
	MFLCONTAINER_RELOAD_FLAG_ITEMBG,	///< ItemBg
	MFLCONTAINER_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define MFLCONTAINER_RELOAD_MASK_OFFSETY         (1<<MFLCONTAINER_RELOAD_FLAG_OFFSETY)
#define MFLCONTAINER_RELOAD_MASK_ITEMHEIGHT        (1<<MFLCONTAINER_RELOAD_FLAG_ITEMHEIGHT)
#define MFLCONTAINER_RELOAD_MASK_SELITEMSIZE         (1<<MFLCONTAINER_RELOAD_FLAG_SELITEMSIZE)
#define MFLCONTAINER_RELOAD_MASK_ITEMBG         (1<<MFLCONTAINER_RELOAD_FLAG_ITEMBG)
/**
* Macro to get flag value
*/
#define MFLCONTAINER_OFFSETY_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&MFLCONTAINER_RELOAD_MASK_OFFSETY)>>MFLCONTAINER_RELOAD_FLAG_OFFSETY)
#define MFLCONTAINER_ITEMHEIGHT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MFLCONTAINER_RELOAD_MASK_ITEMHEIGHT)>>MFLCONTAINER_RELOAD_FLAG_ITEMHEIGHT)
#define MFLCONTAINER_SELITEMSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MFLCONTAINER_RELOAD_MASK_SELITEMSIZE)>>MFLCONTAINER_RELOAD_FLAG_SELITEMSIZE)
#define MFLCONTAINER_ITEMBG_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MFLCONTAINER_RELOAD_MASK_ITEMBG)>>MFLCONTAINER_RELOAD_FLAG_ITEMBG)
/**
* Macro to Set flag value
*/
#define MFLCONTAINER_OFFSETY_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MFLCONTAINER_RELOAD_MASK_OFFSETY))|(((u32)_b)<<MFLCONTAINER_RELOAD_FLAG_OFFSETY)
#define MFLCONTAINER_ITEMHEIGHT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MFLCONTAINER_RELOAD_MASK_ITEMHEIGHT))|(((u32)_b)<<MFLCONTAINER_RELOAD_FLAG_ITEMHEIGHT)
#define MFLCONTAINER_SELITEMSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MFLCONTAINER_RELOAD_MASK_SELITEMSIZE))|(((u32)_b)<<MFLCONTAINER_RELOAD_FLAG_SELITEMSIZE)
#define MFLCONTAINER_ITEMBG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MFLCONTAINER_RELOAD_MASK_ITEMBG))|(((u32)_b)<<MFLCONTAINER_RELOAD_FLAG_ITEMBG)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret MFLContainer_New(MAE_ClsId ClsID, void **ppObj);
boolean MFLContainer_DefHandleEvent(IContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgMFLContainerConstructor(MFLContainer_t *pThis);
void _WdgMFLContainerDestructor(MFLContainer_t *pThis);
void MFLContainer_SetSize(IContainer *pIMFLContainer, WidgetSize_t *pWSize);
MAE_Ret MFLContainer_Add(IContainer *pIMFLContainer, 
						 IWidget *WidgetPtr, 
						 IWidget *RefWidgetPtr, 
						 boolean isUpper, 
						 const void *DescPtr);

void MFLContainer_Invalidate(IContainer *pIMFLContainer, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
/**
* This is default draw function
*/
void MFLContainer_DefDraw(IContainer *pIMFLContainer, IDispCanvas *pIDispCanvas, s32 x, s32 y);


#endif //__MMI_WDG_MFLCONTAINER_PRIV_H__
/*=============================================================*/
// end of file
