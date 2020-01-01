#ifndef __MMI_WDG_GROUP_PRIV_H__
#define __MMI_WDG_GROUP_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"
#include "mmi_cfgsrv.h"
#include "mmi_common_cfg.h"
#include "mmi_mae_util_easing.h"


/*=============================================================*/
// type and define
/*=============================================================*/
#define GROUP_MAX 3
#define ITEM_MAX 4
#define GROUP_ANIMATION_TOTAL_FRAME 10

typedef struct
{
	WidgetBaseEx_t  WdgBase;
    u8 nGroupIdx;
	u8 nFocusItemIdx;
	u8 nCurrAnimIdx;

	boolean bSetID;

	//widget
	IWidget *pItemImgWdg[ITEM_MAX];
	Rect_t  tItemImgRect[ITEM_MAX]; 

	IWidget *pItemTextWdg[ITEM_MAX];
	Rect_t  tItemTextRect[ITEM_MAX]; 

	//show/hide widget
	IWidget *pSlideImgWdg;
	Rect_t  tSlideImgRect; 
    boolean bPressInside;
	
    ICFGSrv *pICFGSrv;
    ITouchSrv *pITouchSrv;
	boolean bHiding;
	boolean bAnimation;
}WdgGroup_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret GroupWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgGroupDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret _WdgGroupConstructor(WdgGroup_t *pThis);
static MAE_Ret _WdgGroupDestructor(WdgGroup_t *pThis);
static MAE_Ret _WdgGroupInitialWdg(WdgGroup_t *pThis);
static void _WdgGroupDraw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static void _WdgGroupSetSize(IWidget *pIWidget,WidgetSize_t *pSize);
static boolean _WdgGroupTSHandler( WdgGroup_t *pThis,MAE_EventId nEvtId, u32 x, u32 y);
static void _WdgGroupDestroyWdg(WdgGroup_t *pThis);
static void _WdgGroupReloadRC(WdgGroup_t *pThis, DisplayMode_e nDispMode);
static void _WdgGroupAnimationEnd(WdgGroup_t *pThis);

#endif //__MMI_WDG_GROUP_PRIV_H__
/*=============================================================*/
// end of file
