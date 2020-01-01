#ifndef __MMI_WDG_OSD_PRIV_H__
#define __MMI_WDG_OSD_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_config.h"
#include "mmi_mae_config_types.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
	WidgetBaseEx_t     WdgBase;           ///< Use this as a base structure.
	ConfigListener_t CfgListener;
	boolean          PrevDrawState;
	IConfig         *pConfig;
} WdgOsd_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret OsdWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgOsdDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
	MAE_Ret _WdgOsdConstructor(WdgOsd_t*);
	void _WdgOsdDestructor(WdgOsd_t *pThis);

	static void _WdgOsdCfgMdlListener(void*, MAECfgCategory_t, MAECfgItemId_t, void*);
	
	static void _WdgOsdDraw(IWidget*, IDispCanvas*, s32, s32);

#endif //__MMI_WDG_OSD_PRIV_H__
/*=============================================================*/
// end of file
