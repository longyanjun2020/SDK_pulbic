#ifndef __MMI_WDG_IMEASSIST_PRIV_H__
#define __MMI_WDG_IMEASSIST_PRIV_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mae_decoratorbase.h"
#include "mmi_mae_imeassistmodel.h"

/*=============================================================*/
// Type and Definitions
/*=============================================================*/
enum ImeAsstWdgFlag_tag
{
	IMEAST_FLAG_VIS_START = 0,
	IMEAST_FLAG_LOCKPOS_START = IMEAST_FLAG_VIS_START+IMEASST_COMPNT_SUM,
	IMEAST_TOTAL_FLAG
};

typedef struct
{
	IWidget       *pWdg;         ///< component Pointer
	WidgetSize_t   WSize;        ///< component size
	Point_t        Position;     ///< component position, relative to RootContainer's coordinate if it's NOT fixed position.
	///<                     relative to IMEAssistWidget's coordinate if it's fixed position.
} ImeAsstWdgComponent_t;

typedef struct
{
	DecoratorEx_t    DecBase;

	WidgetSize_t   ChildSize;

	ImeAsstWdgComponent_t   ComponentData[IMEASST_COMPNT_SUM];

	u32            Flag;                   ///< Properties

	ModelListener_t    DataMdlListener;    ///< Listener to listen own model change event
} _IMEAssistWidget_t;

#define IMEAST_COMPNT_VIS_FLAG(_id)   (IMEAST_FLAG_VIS_START+_id)
#define IMEAST_COMPNT_VIS_MSK(_id)    ((u32)1<<IMEAST_COMPNT_VIS_FLAG(_id))

#define IMEAST_COMPNT_LOCKPOS_FLAG(_id)   (IMEAST_FLAG_LOCKPOS_START+_id)
#define IMEAST_COMPNT_LOCKPOS_MSK(_id)    ((u32)1<<IMEAST_COMPNT_LOCKPOS_FLAG(_id))

#define IMEAST_IS_COMPNT_VIS(_p,_id)         ((_p->Flag&IMEAST_COMPNT_VIS_MSK(_id))>>IMEAST_COMPNT_VIS_FLAG(_id))
#define IMEAST_IS_COMPNT_LOCKPOS(_p,_id)      ((_p->Flag&IMEAST_COMPNT_LOCKPOS_MSK(_id))>>IMEAST_COMPNT_LOCKPOS_FLAG(_id))

#define IMEAST_SET_COMPNT_VIS(_p,_id,_val)      _p->Flag=(_p->Flag&(~IMEAST_COMPNT_VIS_MSK(_id)))|((_val)<<IMEAST_COMPNT_VIS_FLAG(_id))
#define IMEAST_SET_COMPNT_LOCKPOS(_p,_id,_val)   _p->Flag=(_p->Flag&(~IMEAST_COMPNT_LOCKPOS_MSK(_id)))|((_val)<<IMEAST_COMPNT_LOCKPOS_FLAG(_id))

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret IMEAssistWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean IMEAssistWidget_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret _WdgIMEAssistConstructor(_IMEAssistWidget_t *pThis);
__SLDPM_FREE__ void _WdgIMEAssistDestructor(_IMEAssistWidget_t *pThis);

static void IMEAssistWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
__SLDPM_FREE__ static void IMEAssistWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static MAE_Ret IMEAssistWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
__SLDPM_FREE__ static void IMEAssistWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
static MAERet_t IMEAssistWidget_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
__SLDPM_FREE__ static void IMEAssistWidget_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);

/**
*  Helper functions
*/
__SLDPM_FREE__ static void _IMEAssistWidget_ModelChanged(_IMEAssistWidget_t *pThis, u32 dwParam);
__SLDPM_FREE__ static void _IMEAssistWidget_ModelListener(_IMEAssistWidget_t *pThis, ModelEvent_t *pEvent);
__SLDPM_FREE__ static void _IMEAssistWidget_AdjustChildSize(_IMEAssistWidget_t *pThis);
__SLDPM_FREE__ static void _IMEAssistWidget_ForceAdjustChildSize(_IMEAssistWidget_t *pThis);
__SLDPM_FREE__ static void _IMEAssistWidget_AdjustComponentPos(_IMEAssistWidget_t *pThis);
#ifdef __TOUCH_SCREEN_MMI__
static boolean _IMEAssistWidget_HandleTouchEvent(_IMEAssistWidget_t *pThis, MAE_EventId evt, u32 P1, u32 P2);
#endif /* __TOUCH_SCREEN_MMI__ */

#endif /* __MMI_WDG_IMEASSIST_PRIV_H__ */
