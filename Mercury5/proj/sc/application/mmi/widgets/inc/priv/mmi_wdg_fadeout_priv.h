#ifndef __MMI_WDG_FADEOUT_PRIV_H__
#define __MMI_WDG_FADEOUT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
	WidgetBaseEx_t  WdgBase;
	FadeoutLevel_t  FO_lvl;
	Mae_FadeoutSourceType_e eSourceType;
}WdgFadeout_t;


/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret FadeoutWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean WdgFadeoutDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret _WdgFadeoutConstructor(WdgFadeout_t *pThis);

static void _WdgFadeoutDraw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

#endif //__MMI_WDG_FADEOUT_PRIV_H__
/*=============================================================*/
// end of file
