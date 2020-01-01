/**
 * @file    mmi_wdg_animated_menu_priv.h
 * @brief   The internal structure of the main menu animated widget

 */

#ifndef __MMI_WDG_ANIMATED_MENU_PRIV_H__
#define __MMI_WDG_ANIMATED_MENU_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_vectormodel.h"
#include "mae_decoratorbase.h"

#include "mmi_wdg_animated_menu.h"
#include "mmi_common_cfg.h"
#include "mmi_mae_vectormodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/

#define ANIMATION_DEFAULT_FRAME_NUM     (5)
#define ANIMATION_SLIDE_FRAME_NUM       ANIMATION_DEFAULT_FRAME_NUM

#define ANIMATION_3DFLIP_FRAME_NUM      (6)
#define ANIMATION_ROTATE_FRAME_NUM      (4)
#define ANIMATION_LIQUID_FRAME_NUM      (4)
#define ANIMATION_ZOOM_FRAME_NUM        (8)
#define ANIMATION_2DFLIP_FRAME_NUM      (8)
#define ANIMATION_DESTRUCT_FRAME_NUM    (8)
#define ANIMATION_SPLIT_FRAME_NUM       (8)

#define TRANSFORM_ANIMATION_FRAME_NUM   ANIMATION_DEFAULT_FRAME_NUM

#define ANIMATION_DURATION              (16)   // ticks

enum
{
	ANIMATED_3DFLIP_START = 0,
	ANIMATED_3DFLIP_END,

	ANIMATED_3DFLIP_MAX
};
typedef u8 Animated3DflipType_e;

//Flags
enum
{
	WDG_ANIMATED_MENU_FLAG_START = DEC_BASE_FLAG_END,
	WDG_ANIMATED_MENU_FLAG_ACTIVE = WDG_ANIMATED_MENU_FLAG_START,
	WDG_ANIMATED_MENU_FLAG_LOAD_FIRST_FOCUS_IMG,
	WDG_ANIMATED_MENU_FLAG_END
};

typedef struct
{
	DecoratorEx_t   DecBase;

    IListModel      *pListMdl;
    IVectorModel    *pThmIDList;
    IWidget			*pFloatingBoxWidgetStart;
	IWidget			*pFloatingBoxWidgetEnd;

	WdgItemPos_t    tStartWdgItemPos;
    WdgItemPos_t    tEndWdgItemPos;

	SetDisplayMenuAnimationStyle_e   eAnimationStyle;

#ifdef __MMI_ENABLE_ANIMATED_MENU_EFFECT__
	IWidget			*pAnimationEffectWidget;
	AnimatedMenuEffectStyle_e eAnimatedMenuEffectStyle;
	WidgetSize_t	tEffectWdgSize;
	Pos_t				tEffectPos;
	u32					nCurrentEffectFrame;
#endif

	boolean			bTransform;
    u32             nDelay;

} MainMenuAnimatedWdg_t;


/*=============================================================*/
// functions
/*=============================================================*/
//Mask for flags
#define WDG_ANIMATED_MENU_MASK_ACTIVE (1<<WDG_ANIMATED_MENU_FLAG_ACTIVE) 
#define WDG_ANIMATED_MENU_MASK_LOAD_FIRST_FOCUS_IMG (1<<WDG_ANIMATED_MENU_FLAG_LOAD_FIRST_FOCUS_IMG) 

//Get flag macro
#define WDG_ANIMATED_MENU_IS_ACTIVE(_pWdg) \
	(boolean)(((_pWdg)->DecBase.WdgBase.Flags&WDG_ANIMATED_MENU_MASK_ACTIVE)>>WDG_ANIMATED_MENU_FLAG_ACTIVE)
#define WDG_ANIMATED_MENU_IS_LOAD_FIRST_FOCUS_IMG(_pWdg) \
	(boolean)(((_pWdg)->DecBase.WdgBase.Flags&WDG_ANIMATED_MENU_MASK_LOAD_FIRST_FOCUS_IMG )>>WDG_ANIMATED_MENU_FLAG_LOAD_FIRST_FOCUS_IMG )

//Set flag macro
#define WDG_ANIMATED_MENU_SET_ACTIVE(_pWdg, _b) \
	(_pWdg)->DecBase.WdgBase.Flags = ((_pWdg)->DecBase.WdgBase.Flags&(~WDG_ANIMATED_MENU_MASK_ACTIVE))|(((u32)_b)<<WDG_ANIMATED_MENU_FLAG_ACTIVE)
#define WDG_ANIMATED_MENU_SET_LOAD_FIRST_FOCUS_IMG(_pWdg, _b) \
	(_pWdg)->DecBase.WdgBase.Flags = ((_pWdg)->DecBase.WdgBase.Flags&(~WDG_ANIMATED_MENU_MASK_LOAD_FIRST_FOCUS_IMG ))|(((u32)_b)<<WDG_ANIMATED_MENU_FLAG_LOAD_FIRST_FOCUS_IMG )

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret MainMenuAnimatedWdg_New(MAE_ClsId ClsID, void **ppObj);
boolean MainMenuAnimatedWdg_DefHandleEvent(IDecorator*, MAEEvent_t, u32, u32);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret	MainMenuAnimatedWdg_Ctor(MainMenuAnimatedWdg_t *pThis);
static void		MainMenuAnimatedWdg_Dtor(MainMenuAnimatedWdg_t*);

static MAE_Ret	MainMenuAnimatedWdg_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
static MAE_Ret	MainMenuAnimatedWdg_HandleFocusChange(MainMenuAnimatedWdg_t* pThis, u16 nStartIdx, u16 nEndIdx);
void			MainMenuAnimatedWdg_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static void		MainMenuAnimatedWdg_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);
static void MainMenuAnimatedWdg_MenuOnFocusCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pChildWdg);
static MAE_Ret  MainMenuAnimatedWdg_TransformSlide(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static boolean MainMenuAnimatedWdg_SetProperty(MainMenuAnimatedWdg_t *pThis, u32 P1, u32 P2);
static boolean MainMenuAnimatedWdg_GetProperty(MainMenuAnimatedWdg_t *pThis, u32 P1, u32 P2);

static MAE_Ret MainMenuAnimatedWdg_LocateFloatingBox(SetDisplayMenuAnimationStyle_e eAnimationStyle, WdgItemPos_t *pStartItemPos, WdgItemPos_t *pEndItemPos, u32 nStep, WdgItemPos_t *pStartWdgPos, WdgItemPos_t *pEndWdgPos, IADirection_e eDir, float fPercent);

static MAE_Ret  MainMenuAnimatedWdg_TransformNone(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_TransformZoom(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_Transform2DFlip(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_Transform3DFlip(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_TransformLiquid(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_Transform2DRotate(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_TransformDestruct(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static MAE_Ret  MainMenuAnimatedWdg_TransformSplit(MainMenuAnimatedWdg_t *pThis, WdgItemPos_t *pStartItemPos, IBitmap *pStartImg, WdgItemPos_t *pEndItemPos, IBitmap *pEndImg);
static void     MainMenuAnimatedWdg_GetRotateStylePosition(Rect_t *pStartPos, Rect_t *pEndPos, u32 nStep, Rect_t *pPosition);
static void     MainMenuAnimatedWdg_GetDestructStylePosition(Rect_t *pStartPos, Rect_t *pEndPos, u32 nStep, Rect_t *p1stPosition, Rect_t *p2ndPosition);
static void		MainMenuAnimatedWdg_ReloadRC(MainMenuAnimatedWdg_t *pThis, DisplayMode_e nDispMode);

#endif //__MMI_WDG_ANIMATED_MENU_PRIV_H__

/*=============================================================*/
// end of file

