/**
* @file 	mmi_wdg_switchiconitem_priv.h
* @version	$Id: mmi_wdg_switchiconitem_priv.h 32377 2009-06-02 10:50:34Z elvis.chen $
* @brief	xxx
*
*/
#ifndef __MMI_WDG_SWITCHICONITEM_PRIV_H__
#define __MMI_WDG_SWITCHICONITEM_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_switchiconitem.h"
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mmi_mae_model.h"
#include "mae_wdgbackground.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	DecoratorEx_t	DecBase;			///< Use DecoratorEx_t structure as base structure for border.
	ModelListener_t	DataMdlLsn;			///< IDataModel listener.
	IWidget 		*pSwitchIconWdg;	///< A SwitchIcon widget, to display this widget or not, depends on the value in DataModel.
	WdgItemBG_t	tSelectedBG;     ///< background setting for selected mode when icon is disabled
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv      *pITouchSrv;
	u32             nStatusFlag;
#endif //__TOUCH_SCREEN_MMI__
	u16             nIconWidth;         ///< The width for icon
	u16             nIconHeight;        ///< The height for icon
	u8 				nLangDirection;		///< Language direction, the default is LANG_DIR_L_TO_R
	u8				nIconStyle;			///< check, radio, mark, activate,....  refer to Icon_Style_e
	u8				bShowSIconWdg;		///< A boolean value to decide to show switchicon widget or not
	u8				bHighLighted;		///< A boolean value to indicate if this item is highlighted in the list
	u8              nIconPos;           ///< The icon shows on inner/outer of the item wdg
	u32				nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
} SIIWdg_t;

// RELOAD flag
enum
{
	SII_WDG_RELOAD_FLAG_START = 0,
	SII_WDG_RELOAD_FLAG_ICONSTYLE = SII_WDG_RELOAD_FLAG_START,   ///< sICONSTYLE
	SII_WDG_RELOAD_FLAG_SIZE,	///< bSIZE
	SII_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define SII_WDG_RELOAD_MASK_ICONSTYLE   (1<<SII_WDG_RELOAD_FLAG_ICONSTYLE)
#define SII_WDG_RELOAD_MASK_SIZE        (1<<SII_WDG_RELOAD_FLAG_SIZE)
/**
* Macro to get flag value
*/
#define SII_WDG_ICONSTYLE_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SII_WDG_RELOAD_MASK_ICONSTYLE)>>SII_WDG_RELOAD_FLAG_ICONSTYLE)
#define SII_WDG_SIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SII_WDG_RELOAD_MASK_SIZE)>>SII_WDG_RELOAD_FLAG_SIZE)
/**
* Macro to Set flag value
*/
#define SII_WDG_ICONSTYLE_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SII_WDG_RELOAD_MASK_ICONSTYLE))|(((u32)_b)<<SII_WDG_RELOAD_FLAG_ICONSTYLE)
#define SII_WDG_SIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SII_WDG_RELOAD_MASK_SIZE))|(((u32)_b)<<SII_WDG_RELOAD_FLAG_SIZE)

#ifdef __TOUCH_SCREEN_MMI__
//Status Flag enum
enum
{
	SII_WDG_STATUS_FLAG_START = 0,
	SII_WDG_STATUS_FLAG_ICON_PRESSED = SII_WDG_STATUS_FLAG_START, ///< Icon pressed or not
	SII_WDG_STATUS_FLAG_END
};

//Status Flag Mask
#define SII_WDG_MASK_ICON_PRESSED		(1<<SII_WDG_STATUS_FLAG_ICON_PRESSED)

#define SII_WDG_GET_ICON_PRESSED(_pSIIWdg_t) \
	(boolean)(((_pSIIWdg_t)->nStatusFlag&SII_WDG_MASK_ICON_PRESSED)>>SII_WDG_STATUS_FLAG_ICON_PRESSED)

#define SII_WDG_SET_ICON_PRESSED(_pSIIWdg_t, _b) \
	(_pSIIWdg_t)->nStatusFlag = ((_pSIIWdg_t)->nStatusFlag&(~SII_WDG_MASK_ICON_PRESSED))|(((u32)_b)<<SII_WDG_STATUS_FLAG_ICON_PRESSED)
#endif //__TOUCH_SCREEN_MMI__



/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret SwitchIconItemWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean SIIWdg_DefHandleEvent(IDecorator *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret SIIWdgStructCtor(SIIWdg_t *pThis);
static void SIIWdgStructDtor(SIIWdg_t *pThis);
static void SIIWdg_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
static void SIIWdg_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
boolean SIIWdg_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
static MAE_Ret SIIWdg_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
static void SIIWdg_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
static MAE_Ret SIIWdg_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
static void SIIWdg_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);

/*------------------------------------------------------------------------------------------
* For other functions
------------------------------------------------------------------------------------------*/
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _SIIWdg_ReloadRC(SIIWdg_t *pThis, DisplayMode_e nDispMode);
#endif

#endif //__MMI_WDG_SWITCHICONITEM_PRIV_H__
/*=============================================================*/
// end of file
