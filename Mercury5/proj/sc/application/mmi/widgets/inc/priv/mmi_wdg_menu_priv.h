#ifndef __MMI_WDG_MENU_PRIV_H__
#define __MMI_WDG_MENU_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_decoratorbase.h"
#include "mmi_wdg_menu.h"
#include "mmi_wdg_softkey.h"
#include "mmi_mae_softkeymodel.h"
#include "mmi_mae_menumodel.h"
#include "mae_wdgbackground.h"
#include "mmi_wdg_list.h"
#include "img_data.h"
#include "mmi_CusDefine.h"
#if defined(__FEATURE_MGL__)
#include "mgl_Egl.h"
#include "mgl_Core_Types.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Core_Shape.h"
#endif

/*=============================================================*/
// type and define
/*=============================================================*/
/**
* Flags in MenuWidget_t
*/
enum
{
	MENUWDG_FLAG_START = 0,
	MENUWDG_FLAG_NUMERIC_ACCESS = MENUWDG_FLAG_START,	///< To quick access item by numeric key or not
	MENUWDG_FLAG_AUTO_TOGGLE_ITEM,						///< To auto toggle item when selected or not
	MENUWDG_FLAG_SHOW_MARKED_ITEM_NUMBER,				///< To show total checked number in title or not
	MENUWDG_FLAG_SHOW_TOTAL_ITEM_NUMBER,				///< To show total item number in title or not
	MENUWDG_FLAG_SHOW_EMPTY_TEXT,				        ///< To show total item number in title or not
    MENUWDG_FLAG_MENUTREE,
    MENUWDG_FLAG_MODIFYSOFTKEY,
	MENUWDG_FLAG_END
};	//Note: MENUWDG_FLAG_END is 3 now.

#define MENUWDG_NUMERIC_ICON_MAX	CUS_MENUWDG_NUMERIC_ICON_MAX

#if defined(__FEATURE_MGL__)
#define MENUWDG_ITEM_ROTATE_ANGLE           (15.0f)
#define MENUWDG_ROTATE_ANGLE_90_DEGREE      (90.0f)
#define MENUWDG_ITEM_ROTATE_TIMER           (40)
#endif

/**
* Flag Mask
*/
#define MENUWDG_MASK_NUMERIC_ACCESS				(1<<MENUWDG_FLAG_NUMERIC_ACCESS)
#define MENUWDG_MASK_AUTO_TOGGLE_ITEM			(1<<MENUWDG_FLAG_AUTO_TOGGLE_ITEM)
#define MENUWDG_MASK_SHOW_MARKED_ITEM_NUMBER	(1<<MENUWDG_FLAG_SHOW_MARKED_ITEM_NUMBER)
#define MENUWDG_MASK_SHOW_TOTAL_ITEM_NUMBER		(1<<MENUWDG_FLAG_SHOW_TOTAL_ITEM_NUMBER)
#define MENUWDG_MASK_SHOW_EMPTY_TEXT			(1<<MENUWDG_FLAG_SHOW_EMPTY_TEXT)
#define MENUWDG_MASK_MENUTREE                   (1<<MENUWDG_FLAG_MENUTREE)
#define MENUWDG_MASK_MODIFYSOFTKEY              (1<<MENUWDG_FLAG_MODIFYSOFTKEY)

/**
* Macro to get flag value
*/
#define MENUWDG_IS_NUMERIC_ACCESS(_pMenuWdg) \
	(boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_NUMERIC_ACCESS)>>MENUWDG_FLAG_NUMERIC_ACCESS)
#define MENUWDG_IS_AUTO_TOGGLE_ITEM(_pMenuWdg) \
	(boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_AUTO_TOGGLE_ITEM)>>MENUWDG_FLAG_AUTO_TOGGLE_ITEM)
#define MENUWDG_IS_SHOW_MARKED_ITEM_NUMBER(_pMenuWdg) \
	(boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_SHOW_MARKED_ITEM_NUMBER)>>MENUWDG_FLAG_SHOW_MARKED_ITEM_NUMBER)
#define MENUWDG_IS_SHOW_TOTAL_ITEM_NUMBER(_pMenuWdg) \
	(boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_SHOW_TOTAL_ITEM_NUMBER)>>MENUWDG_FLAG_SHOW_TOTAL_ITEM_NUMBER)
#define MENUWDG_IS_SHOW_EMPTY_TEXT(_pMenuWdg) \
	(boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_SHOW_EMPTY_TEXT)>>MENUWDG_FLAG_SHOW_EMPTY_TEXT)
#define MENUWDG_IS_MENUTREE(_pMenuWdg) \
    (boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_MENUTREE)>>MENUWDG_FLAG_MENUTREE)
#define MENUWDG_IS_MODIFYSOFTKEY(_pMenuWdg) \
        (boolean)(((_pMenuWdg)->nFlags&MENUWDG_MASK_MODIFYSOFTKEY)>>MENUWDG_FLAG_MODIFYSOFTKEY)

/**
* Macro to Set flag value
*/
#define MENUWDG_SET_NUMERIC_ACCESS(_pMenuWdg, _b) \
	(_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_NUMERIC_ACCESS))|(((u32)_b)<<MENUWDG_FLAG_NUMERIC_ACCESS)
#define MENUWDG_SET_AUTO_TOGGLE_ITEM(_pMenuWdg, _b) \
	(_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_AUTO_TOGGLE_ITEM))|(((u32)_b)<<MENUWDG_FLAG_AUTO_TOGGLE_ITEM)
#define MENUWDG_SET_SHOW_MARKED_ITEM_NUMBER(_pMenuWdg, _b) \
	(_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_SHOW_MARKED_ITEM_NUMBER))|(((u32)_b)<<MENUWDG_FLAG_SHOW_MARKED_ITEM_NUMBER)
#define MENUWDG_SET_SHOW_TOTAL_ITEM_NUMBER(_pMenuWdg, _b) \
	(_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_SHOW_TOTAL_ITEM_NUMBER))|(((u32)_b)<<MENUWDG_FLAG_SHOW_TOTAL_ITEM_NUMBER)
#define MENUWDG_SET_SHOW_EMPTY_TEXT(_pMenuWdg, _b) \
	(_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_SHOW_EMPTY_TEXT))|(((u32)_b)<<MENUWDG_FLAG_SHOW_EMPTY_TEXT)
#define MENUWDG_SET_MENUTREE(_pMenuWdg, _b) \
    (_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_MENUTREE))|(((u32)_b)<<MENUWDG_FLAG_MENUTREE)
#define MENUWDG_SET_MODIFYSOFTKEY(_pMenuWdg, _b) \
    (_pMenuWdg)->nFlags = ((_pMenuWdg)->nFlags&(~MENUWDG_MASK_MODIFYSOFTKEY))|(((u32)_b)<<MENUWDG_FLAG_MODIFYSOFTKEY)

typedef struct {
	DecoratorEx_t		DecBase;
	MAE_ClsId			nItemWdgClsId;
    boolean             bIsUserDefItem;
	u32					nFirstIndex;
	u32					nHighlightedIndex;
	u32					nSelectedID;
	u32					nTotalSize;
	u32					nCheckedInfo;
	SoftkeyID_e			nDefaultSK[NUM_SK];
	SoftkeyID_e			nUnavilItemSK[NUM_SK];
	WidgetSize_t		gridItemSize;
	IWidget				*pListWdg;
	IWidget				*pScrollWdg;
	IWidget				*pItemWdg;
	IWidget				*pTitle2Wdg;
	MAE_WChar			*pTitle1Text;
	MAE_WChar			*pTitle2Text;
	HistoryInfo_t		stHistory;
	FocusInfo_t			stFocus;
	IMenuModel			*pIMenuModel;
	IModel				*pItemWdgDataMdl;   // Model from item widget
	ISoftkeyModel		*pISotkeyMdl;
	ModelListener_t		MenuMdlLsn;			// model listener for menu model
	u32					nFlags;
	u32					nFocusItemBgImgID;
	u32					nEmptyTextID;
	RGBColor_t			stEmptyTextColor;
	u16					nMaxCheckedNum;
	u16					nMinCheckedNum;
	GridItemNumInfo_t	stGridItemNum;
	AutoUpdate_t		nAutoUpdateTitle;
	ItemDisplayStyle_t	nItemDispStyle;
	ScrollStyle_t		nScrollStyle;
	OptionMenuStyle_t	nOptionMenuStyle;
	u8					nCheckStyle;
    u32 u32UserActionSoftkeyId;
    u32 u32UserBackSoftkeyId;
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
    MaeMenuWidgetTree_t sMenuTreeInf;
	IImage *aNumericIcon[MENUWDG_NUMERIC_ICON_MAX];
	IImage *pArrowIcon;

#ifdef __TEXT_ENUM_MENUITEM_MMI__
	IWidget				*pNumericTextWdg;
	RGBColor_t          nItemTextColor;
	RGBColor_t          nHighLightItemTextColor;
#endif  //__TEXT_ENUM_MENUITEM_MMI__

#if defined(__FEATURE_MGL__)
    u8                  nMaxFlipAniItems;
    u8                  nMaxDisplayItems;
	mgl_u16             nSceneHandle;
	mgl_u32             nItemTextureId[MENU_ANIMATION_FLIP_ITEM_MAX];
    boolean             bClockwise;
	u32                 nFlipEffectNodeId[MENU_ANIMATION_FLIP_ITEM_MAX];
    mgl_float           nFlipItemAngle[MENU_ANIMATION_FLIP_ITEM_MAX];
    u32                 nCurrentItemNum;
    u32                 nNextItemNum;
    IBitmap             *pImgCurViewItem[MENU_ANIMATION_FLIP_ITEM_MAX];
    IBitmap             *pImgNextViewItem[MENU_ANIMATION_FLIP_ITEM_MAX];
    Menu_FlipAnimStyle_e eItemFlipStyle;
    FlipItemAnimationState_e eItemAniState;
#endif

} MenuWidget_t;

#define MENUWIDGET_UNDEFINE_IMAGE_ID		0xFFFFFFFF
#define MENUWIDGET_MARK_INFO_MAX_LENGTH		8

// RELOAD flag
enum
{
	MENU_WDG_RELOAD_FLAG_START = 0,
	MENU_WDG_RELOAD_FLAG_SHOW_MARKED_ITEMNUM = MENU_WDG_RELOAD_FLAG_START,   ///< bShowMarkedItemNum
	MENU_WDG_RELOAD_FLAG_SHOW_TOTALNUM,	///< bShowTotalNum
	MENU_WDG_RELOAD_FLAG_SHOW_EMPTYTEXT,	///< bShowEmptyText
	MENU_WDG_RELOAD_FLAG_DEFAULTSK,	///< nDefaultSK
	MENU_WDG_RELOAD_FLAG_UNAVILITEMSK,	///< nUnavilItemSK
	MENU_WDG_RELOAD_FLAG_CHECKSTYLE,	///< nCheckStyle
	MENU_WDG_RELOAD_FLAG_FOCUSITEMBG_IMGID,	///< nFocusItemBgImgID
	MENU_WDG_RELOAD_FLAG_OPTIONMENUSTYLE,	///< nOptionMenuStyle
	MENU_WDG_RELOAD_FLAG_SCROLLSTYLE,	///< nScrollStyle
	MENU_WDG_RELOAD_FLAG_EMPTYTEXTID,	///< nEmptyTextID
	MENU_WDG_RELOAD_FLAG_EMPTYTEXTCOLOR,	///< stEmptyTextColor
	MENU_WDG_RELOAD_FLAG_GRID_ITEMNUM,	///< stGridItemNum
	MENU_WDG_RELOAD_FLAG_ITEMHEIGHT,	///< nItemHeight
	MENU_WDG_RELOAD_FLAG_FOCUS_ITEMHEIGHT,	///< nFocusHeight
	MENU_WDG_RELOAD_FLAG_BG_IMG,
	MENU_WDG_RELOAD_FLAG_BG_COLOR,
	MENU_WDG_RELOAD_FLAG_ITEM_TEXT_COLOR,	///nItemTextColor
	MENU_WDG_RELOAD_FLAG_ITEMWIDTH,
	MENU_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define MENU_WDG_RELOAD_MASK_SHOW_MARKED_ITEMNUM         (1<<MENU_WDG_RELOAD_FLAG_SHOW_MARKED_ITEMNUM)
#define MENU_WDG_RELOAD_MASK_SHOW_TOTALNUM        (1<<MENU_WDG_RELOAD_FLAG_SHOW_TOTALNUM)
#define MENU_WDG_RELOAD_MASK_SHOW_EMPTYTEXT         (1<<MENU_WDG_RELOAD_FLAG_SHOW_EMPTYTEXT)
#define MENU_WDG_RELOAD_MASK_DEFAULTSK        (1<<MENU_WDG_RELOAD_FLAG_DEFAULTSK)
#define MENU_WDG_RELOAD_MASK_UNAVILITEMSK         (1<<MENU_WDG_RELOAD_FLAG_UNAVILITEMSK)
#define MENU_WDG_RELOAD_MASK_CHECKSTYLE        (1<<MENU_WDG_RELOAD_FLAG_CHECKSTYLE)
#define MENU_WDG_RELOAD_MASK_FOCUSITEMBG_IMGID         (1<<MENU_WDG_RELOAD_FLAG_FOCUSITEMBG_IMGID)
#define MENU_WDG_RELOAD_MASK_OPTIONMENUSTYLE        (1<<MENU_WDG_RELOAD_FLAG_OPTIONMENUSTYLE)
#define MENU_WDG_RELOAD_MASK_SCROLLSTYLE         (1<<MENU_WDG_RELOAD_FLAG_SCROLLSTYLE)
#define MENU_WDG_RELOAD_MASK_EMPTYTEXTID        (1<<MENU_WDG_RELOAD_FLAG_EMPTYTEXTID)
#define MENU_WDG_RELOAD_MASK_EMPTYTEXTCOLOR         (1<<MENU_WDG_RELOAD_FLAG_EMPTYTEXTCOLOR)
#define MENU_WDG_RELOAD_MASK_GRID_ITEMNUM        (1<<MENU_WDG_RELOAD_FLAG_GRID_ITEMNUM)
#define MENU_WDG_RELOAD_MASK_ITEMHEIGHT        (1<<MENU_WDG_RELOAD_FLAG_ITEMHEIGHT)
#define MENU_WDG_RELOAD_MASK_ITEMWIDTH        (1<<MENU_WDG_RELOAD_FLAG_ITEMWIDTH)
#define MENU_WDG_RELOAD_MASK_FOCUS_ITEMHEIGHT        (1<<MENU_WDG_RELOAD_FLAG_FOCUS_ITEMHEIGHT)
#define MENU_WDG_RELOAD_MASK_BG_IMG        (1<<MENU_WDG_RELOAD_FLAG_BG_IMG)
#define MENU_WDG_RELOAD_MASK_BG_COLOR        (1<<MENU_WDG_RELOAD_FLAG_BG_COLOR)
#define MENU_WDG_RELOAD_MASK_ITEM_TEXT_COLOR        (1<<MENU_WDG_RELOAD_FLAG_ITEM_TEXT_COLOR)


/**
* Macro to get flag value
*/
#define MENU_WDG_SHOW_MARKED_ITEMNUM_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_SHOW_MARKED_ITEMNUM)>>MENU_WDG_RELOAD_FLAG_SHOW_MARKED_ITEMNUM)
#define MENU_WDG_SHOW_TOTALNUM_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_SHOW_TOTALNUM)>>MENU_WDG_RELOAD_FLAG_SHOW_TOTALNUM)
#define MENU_WDG_SHOW_EMPTYTEXT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_SHOW_EMPTYTEXT)>>MENU_WDG_RELOAD_FLAG_SHOW_EMPTYTEXT)
#define MENU_WDG_DEFAULTSK_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_DEFAULTSK)>>MENU_WDG_RELOAD_FLAG_DEFAULTSK)
#define MENU_WDG_UNAVILITEMSK_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_UNAVILITEMSK)>>MENU_WDG_RELOAD_FLAG_UNAVILITEMSK)
#define MENU_WDG_CHECKSTYLE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_CHECKSTYLE)>>MENU_WDG_RELOAD_FLAG_CHECKSTYLE)
#define MENU_WDG_FOCUSITEMBG_IMGID_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_FOCUSITEMBG_IMGID)>>MENU_WDG_RELOAD_FLAG_FOCUSITEMBG_IMGID)
#define MENU_WDG_OPTIONMENUSTYLE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_OPTIONMENUSTYLE)>>MENU_WDG_RELOAD_FLAG_OPTIONMENUSTYLE)
#define MENU_WDG_SCROLLSTYLE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_SCROLLSTYLE)>>MENU_WDG_RELOAD_FLAG_SCROLLSTYLE)
#define MENU_WDG_EMPTYTEXTID_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_EMPTYTEXTID)>>MENU_WDG_RELOAD_FLAG_EMPTYTEXTID)
#define MENU_WDG_EMPTYTEXTCOLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_EMPTYTEXTCOLOR)>>MENU_WDG_RELOAD_FLAG_EMPTYTEXTCOLOR)
#define MENU_WDG_GRID_ITEMNUM_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_GRID_ITEMNUM)>>MENU_WDG_RELOAD_FLAG_GRID_ITEMNUM)
#define MENU_WDG_ITEMHEIGHT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_ITEMHEIGHT)>>MENU_WDG_RELOAD_FLAG_ITEMHEIGHT)
#define MENU_WDG_ITEMWIDTH_IS_MODIFIED(_pWdg) \
        (boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_ITEMWIDTH)>>MENU_WDG_RELOAD_FLAG_ITEMWIDTH)
#define MENU_WDG_FOCUS_ITEMHEIGHT_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_FOCUS_ITEMHEIGHT)>>MENU_WDG_RELOAD_FLAG_FOCUS_ITEMHEIGHT)
#define MENU_WDG_ITEM_TEXT_COLOR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&MENU_WDG_RELOAD_MASK_ITEM_TEXT_COLOR)>>MENU_WDG_RELOAD_FLAG_ITEM_TEXT_COLOR)

/**
* Macro to Set flag value
*/
#define MENU_WDG_SHOW_MARKED_ITEMNUM_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_SHOW_MARKED_ITEMNUM))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_SHOW_MARKED_ITEMNUM)
#define MENU_WDG_SHOW_TOTALNUM_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_SHOW_TOTALNUM))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_SHOW_TOTALNUM)
#define MENU_WDG_SHOW_EMPTYTEXT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_SHOW_EMPTYTEXT))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_SHOW_EMPTYTEXT)
#define MENU_WDG_DEFAULTSK_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_DEFAULTSK))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_DEFAULTSK)
#define MENU_WDG_UNAVILITEMSK_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_UNAVILITEMSK))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_UNAVILITEMSK)
#define MENU_WDG_CHECKSTYLE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_CHECKSTYLE))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_CHECKSTYLE)
#define MENU_WDG_FOCUSITEMBG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_FOCUSITEMBG_IMGID))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_FOCUSITEMBG_IMGID)
#define MENU_WDG_OPTIONMENUSTYLE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_OPTIONMENUSTYLE))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_OPTIONMENUSTYLE)
#define MENU_WDG_SCROLLSTYLE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_SCROLLSTYLE))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_SCROLLSTYLE)
#define MENU_WDG_EMPTYTEXTID_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_EMPTYTEXTID))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_EMPTYTEXTID)
#define MENU_WDG_EMPTYTEXTCOLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_EMPTYTEXTCOLOR))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_EMPTYTEXTCOLOR)
#define MENU_WDG_GRID_ITEMNUM_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_GRID_ITEMNUM))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_GRID_ITEMNUM)
#define MENU_WDG_ITEMHEIGHT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_ITEMHEIGHT))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_ITEMHEIGHT)
#define MENU_WDG_FOCUS_ITEMHEIGHT_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_FOCUS_ITEMHEIGHT))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_FOCUS_ITEMHEIGHT)
#define MENU_WDG_ITEMWIDTH_SET_MODIFIED(_pWdg, _b) \
        (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_ITEMWIDTH))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_ITEMWIDTH)
#define MENU_WDG_FOCUS_BG_IMG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_BG_IMG))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_BG_IMG)
#define MENU_WDG_FOCUS_BG_COLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_BG_COLOR))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_BG_COLOR)
#define MENU_WDG_ITEM_TEXT_COLOR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~MENU_WDG_RELOAD_MASK_ITEM_TEXT_COLOR))|(((u32)_b)<<MENU_WDG_RELOAD_FLAG_ITEM_TEXT_COLOR)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret MenuWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean MenuWidget_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret MenuWidgetBaseStrucCtor(MenuWidget_t *pThis);
void MenuWidgetBaseStrucDtor(IDecorator *pIDecorator);
void MenuWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
__SLDPM_FREE__ void MenuWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
__SLDPM_FREE__ void MenuWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
__SLDPM_FREE__ MAE_Ret MenuWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
__SLDPM_FREE__ boolean MenuWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);

__SLDPM_FREE__ MAE_Ret MenuWidget_AddEvtListener(IDecorator *pIDecorator, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);
MAE_Ret MenuWidget_CancelEvtListener(IDecorator *pIDecorator, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);

__SLDPM_FREE__ void MenuWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
MAE_Ret MenuWidget_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
__SLDPM_FREE__ void MenuWidget_CalGridItemSize(MenuWidget_t *pThis, GridItemNumInfo_t *pGridItemNum, boolean bChangeItemSize);
__SLDPM_FREE__ boolean MenuWidget_SetProperty(MenuWidget_t *pThis, u32 P1, u32 P2);
__SLDPM_FREE__ boolean MenuWidget_GetProperty(MenuWidget_t *pThis, u32 P1, u32 P2);
__SLDPM_FREE__ void MenuWidget_ListWdgFocusChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData,IWidget *pListWidget);
void MenuWidget_ListWdgFocusSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pListWidget);
void MenuWidget_ListWdgFocusLongPressCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pListWidget);
void MenuWidget_ListWdgBoundsTop(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pListWidget);
void MenuWidget_ListWdgBoundsBottom(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pListWidget);
void MenuWidget_SIIWdgSwitchingNotifyCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, boolean bCheck, IWidget *pReserve);
__SLDPM_FREE__ void MenuWidget_MenuModelListener(void *pUsrData, MenuModelEvent_t *pMdlEvent);
__SLDPM_FREE__ MAE_Ret MenuWidget_CreateItemWidget(MenuWidget_t *pThis, MAE_ClsId cidItem);
__SLDPM_FREE__ MAE_Ret MenuWidget_CreateListWidget(MenuWidget_t *pThis, MAE_ClsId cidMenuWdg);
__SLDPM_FREE__ u8 MenuWidget_CalMaxItemsOnScreen(MenuWidget_t *pThis);
void MenuWidget_DisplayMarkedInfo(MenuWidget_t *pThis);
void MenuWidget_RecalulateMarkedNumber(MenuWidget_t *pThis, u32 nTotalSize);
void MenuWidget_CheckRadioItemSelectable(MenuWidget_t *pThis, ItemFlag_t eItemFlags);
__SLDPM_FREE__ void MenuWidget_SetItemDispHeight(MenuWidget_t *pThis, boolean bSetDefaultItemSize);

__SLDPM_FREE__ void MenuWidget_DrawTitleSoftkeys(MenuWidget_t *pThis, u32 nItemIndex);
__SLDPM_FREE__ void MenuWidget_CreateScrollWidget(MenuWidget_t *pThis, ScrollStyle_t nScrollStyle);

#if defined(__FEATURE_MGL__)
static MAE_Ret MenuWidget_GetItemOrderByNodeId(MenuWidget_t *pThis, u32 nNodeId, u8 *eRetVal);
static void MenuWidget_InitAnimationObject(MenuWidget_t *pThis);
static void MenuWidget_ReleaseAnimationObject(MenuWidget_t *pThis);
static void MenuWidget_RotateListItem(MenuWidget_t *pThis, FlipItemOrder_e eItemOrder, IBitmap *pRawData, mgl_float nRotAngle);
static void MenuWidget_ItemFlipEffectCB(mgl_u32 nodeID, mgl_void *pUserData);
static void MenuWidget_ReleaseItemTexture(mgl_void *pUserData, FlipItemOrder_e eItemOrder);
void MenuWidget_ItemFlipAnimDrawCB(void *pUserData);
#endif

//data model adaptset relative function
__SLDPM_FREE__ void MenuWidget_GridItemWdgAdaptSetFree(void *pData, IBase *pOwner);
void MenuWidget_MarkItemWdgAdaptSetFree(void *pData, IBase *pOwner);
void MenuWidget_NumericItemWdgAdaptSetFree(void *pData, IBase *pOwner);
void MenuWidget_OptionNumericItemWdgAdaptSetFree(void *pData, IBase *pOwner);
void MenuWidget_OptionItemWdgAdaptSetFree(void *pData, IBase *pOwner);
__SLDPM_FREE__ void MenuWidget_GridItemWdgAdaptSet(void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pnLenOut, PfnModelFree *ppFreeFunc, IBase **ppOwner);
void MenuWidget_MarkItemWdgAdaptSet(void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pnLenOut, PfnModelFree *ppFreeFunc, IBase **ppOwner);
__SLDPM_FREE__ void MenuWidget_NumericItemWdgAdaptSet(void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pnLenOut, PfnModelFree *ppFreeFunc, IBase **ppOwner);
__SLDPM_FREE__ void MenuWidget_NormalItemWdgAdaptSet(void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pnLenOut, PfnModelFree *ppFreeFunc, IBase **ppOwner);
void MenuWidget_ScrollFinishWdgCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pListWidget);

#endif //__MMI_WDG_MENU_PRIV_H__
/*=============================================================*/
// end of file
