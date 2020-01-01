#ifndef __MMI_WDG_LIST_PRIV_H__
#define __MMI_WDG_LIST_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_gridwidgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/

/*------------------------------------------------------------------------------------------
* new function constructor and destructor for widget base
------------------------------------------------------------------------------------------*/
__SLDPM_FREE__ MAE_Ret ListWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean ListWidget_HandleEvent(IDecorator *pDecorator, MAE_EventId evt, u32 P1, u32 P2);

MAE_Ret ListWidget_Constructor(GridWdgBase_t *pThis);

#endif //__MMI_WDG_LIST_PRIV_H__
/*=============================================================*/
// end of file
