/**
 * @file    mmi_wdg_dummy_priv.h
 * @author  alison.chen@mstarsemi.com
 * 
 * @version $Id: mmi_wdg_dummy_priv.h 4291 2007-11-19 03:56:54Z alison.chen $
 *
 *
 * @brief   
 *
 */

#ifndef __MMI_WDG_DUMMY_PRIV_H__
#define __MMI_WDG_DUMMY_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	 WidgetBaseEx_t WdgBase;
} WdgDummy_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret DummyWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgDummyDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
	static MAE_Ret _WdgDummyConstructor(WdgDummy_t*);


#endif //__MMI_WDG_DUMMY_PRIV_H__
/*=============================================================*/
// end of file
