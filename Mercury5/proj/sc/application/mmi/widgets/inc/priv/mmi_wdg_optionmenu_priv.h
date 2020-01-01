#ifndef __MMI_WDG_OPTIONMENU_PRIV_H__
#define __MMI_WDG_OPTIONMENU_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_optionmenu.h"
#include "mae_abscontainerbase.h"
#include "img_data.h"
#include "mmi_wdg_menu.h"
#include "mmi_mae_menumodel.h"
#include "mmi_wdg_fadeout.h"
#include "mmi_mae_softkeymodel.h"

#ifdef __OPTION_MENU_3D_EXT__
#include "mae_glwidget_common.h"
#include "mae_widget_common.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Core_shape.h"
#include "mgl_Core_types.h"
#include "mmi_mae_bitmap_types.h"
#include "mmi_mae_graphic.h"
#include "mmi_mae_dib.h"
#include "mmi_mae_dib_types.h"
#endif

/*=============================================================*/
// type and define
/*=============================================================*/

typedef struct
{
    AbsContainerBase_t ACntrBase;
    ISoftkeyModel *pISoftkeyMdl;
#ifdef __OPTION_MENU_3D_EXT__
    IWidget *pL1AbsContainer;
    IWidget *pL1TopBgImage;
    IWidget *pL1CenterBgImage;
    IWidget *pL1BottomBgImage;
#endif
    IWidget *pIOptMenuWdg_L1;
#ifdef __OPTION_MENU_3D_EXT__
    IWidget *pL2AbsContainer;
    IWidget *pL2TopBgImage;
    IWidget *pL2CenterBgImage;
    IWidget *pL2BottomBgImage;
#endif
    IWidget *pIOptMenuWdg_L2;
    IWidget *pIFadeOutWdg;
    IMenuModel *pIMenuModel_L1;
    IMenuModel *pIMenuModel_L2;
    u32 nPrevModelSize_L1;
    u32 nPrevModelSize_L2;
#ifndef __OPTIONMENU_SUPPORT_ONE_VIEW_MODEL__
    IModel *pIViewModel_L1;
    IModel *pIViewModel_L2;
#endif // #ifndef __OPTIONMENU_SUPPORT_ONE_VIEW_MODEL__
    ModelListener_t ViewMdlListener_L1;
    ModelListener_t ViewMdlListener_L2;
	s32 sL1PosX;
	s32 sL2PosX;
	s32 sMenuOffsetY;

    u32 nReloadRCFlag;      ///< the flag record which rc property has been modified outside, those are not reload

#ifdef __OPTION_MENU_3D_EXT__
    mgl_u16 u16SceneHandleId;
    mgl_u32 ContainerNode[2];
    u32 u32AnimationFrame;
    boolean bL1Animating;
    boolean bL2Animating;
    u32 u32L1TextureID;
    u32 u32L2TextureID;
    IBitmap *pL1Bitmap;
    IBitmap *pL2Bitmap;

    IImage *pImageObj[3];
    boolean bDecodeDone[3];

#endif
}_MAE_OptionMenuWidget;

enum
{
	OPTMENU_WDG_RELOAD_FLAG_START = 0,
	OPTMENU_WDG_RELOAD_FLAG_LAYOUTSTYLE = OPTMENU_WDG_RELOAD_FLAG_START,
	OPTMENU_WDG_RELOAD_FLAG_L2POSX,
	OPTMENU_WDG_RELOAD_FLAG_END
};
/**
* Flag Mask
*/
#define OPTMENU_WDG_RELOAD_MASK_LAYOUTSTYLE         (1<<OPTMENU_WDG_RELOAD_FLAG_LAYOUTSTYLE)
/**
* Macro to get flag value
*/
#define OPTMENU_WDG_LAYOUTSTYLE_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&OPTMENU_WDG_RELOAD_MASK_LAYOUTSTYLE)>>OPTMENU_WDG_RELOAD_FLAG_LAYOUTSTYLE)
/**
* Macro to Set flag value
*/
#define OPTMENU_WDG_LAYOUTSTYLE_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~OPTMENU_WDG_RELOAD_MASK_LAYOUTSTYLE))|(((u32)_b)<<OPTMENU_WDG_RELOAD_FLAG_LAYOUTSTYLE)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret OptionMenuWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean OptionMenuWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret OptionMenuWidgetConstructor(_MAE_OptionMenuWidget *pThis );
static void OptionMenuWidget_Dstor(_MAE_OptionMenuWidget *pThis);

static void OptionMenuWidget_Draw(IAbsContainer *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);
/*	deprecated
static MAE_Ret _OptionMenuWidget_SetMdlListener(IAbsContainer *pThis, IWidget *pIWidget, ModelListener_t *pMdlLsnPtr);
*/

static MAE_Ret OptionMenuWidget_Init(IAbsContainer * pIAbsContainer);
static void _OptionMenuWidget_ViewModelListener_L1(void *pUserData, ModelEvent_t *pMdlEvent);
static void _OptionMenuWidget_ViewModelListener_L2(void *pUserData, ModelEvent_t *pMdlEvent);
static void _OptionMenuWidget_CloseL2(_MAE_OptionMenuWidget *pThis);

static void _OptionMenuWidget_UpdateL1Model(_MAE_OptionMenuWidget *pThis);
static void _OptionMenuWidget_UpdateL2Model(_MAE_OptionMenuWidget *pThis);

#if defined (__TOUCH_SCREEN_MMI__) && !defined  (__OPTION_MENU_3D_EXT__)
static void _OptionMenuWidget_Notify(_MAE_OptionMenuWidget 	*pThis,
							  		 IWidget 				*pIWidget,
#ifndef __OPTIONMENU_SUPPORT_ONE_VIEW_MODEL__
							  		 IModel 				*pViewMdl,
#endif	// __OPTIONMENU_SUPPORT_ONE_VIEW_MODEL__
							  		 u32					evtCode);
#endif	// __TOUCH_SCREEN_MMI__

#endif /* __MMI_WDG_OPTIONMENU_PRIV_H__ */
